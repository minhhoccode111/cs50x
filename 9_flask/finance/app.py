import os
from threading import current_thread

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from werkzeug.security import check_password_hash, generate_password_hash

from flask_session import Session
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    current_user_id = session["user_id"]

    # print(current_user_id)

    user_info = db.execute("SELECT cash FROM users WHERE id = ?", current_user_id)[0]
    user_stocks = db.execute(
        "SELECT symbol, shares FROM user_stocks WHERE user_id = ?", current_user_id
    )

    sum_stocks = 0
    # Look up the stock and current price
    for index, stock in enumerate(user_stocks):
        lookup_result = lookup(stock["symbol"])
        if not lookup_result:
            return apology("invalid symbol", 403)
        stock_sum = round(stock["shares"] * lookup_result["price"], 2)
        user_stocks[index]["sum_stock"] = stock_sum
        user_stocks[index]["price_stock"] = lookup_result["price"]
        sum_stocks += stock_sum

    print(round(user_info["cash"], 2))
    print(sum_stocks)
    print(user_stocks)
    return render_template(
        "index.html",
        cash=round(user_info["cash"], 2),
        sum_stocks=round(sum_stocks, 2),
        stocks=user_stocks,
    )


def is_valid_shares(shares):
    # Check if the string is a non-zero digit
    if shares.isdigit():
        shares = int(shares)
        if 1 <= shares:
            return True
        return False


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate stock symbol input
        if not symbol or symbol.isspace() or symbol == "":
            return apology("must provide symbol", 400)

        # Validate shares input
        if not shares or not is_valid_shares(shares):
            return apology("must provide valid number of shares", 400)

        # Look up the stock
        lookup_result = lookup(symbol)
        if not lookup_result:
            return apology("invalid symbol", 400)

        # Get the current price of the stock
        current_price = lookup_result["price"]
        total_cost = current_price * int(shares)

        try:
            # Get the user's cash balance
            current_user_id = session["user_id"]
            user_cash = db.execute(
                "SELECT cash FROM users WHERE id = ?", current_user_id
            )[0]["cash"]
            # Ensure user can afford the stock purchase
            if total_cost > user_cash:
                return apology("can't afford", 400)

            # Insert transaction into transactions table
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
                current_user_id,
                symbol,
                shares,
                current_price,
                "buy",
            )

            # Update user's cash balance
            db.execute(
                "UPDATE users SET cash = cash - ? WHERE id = ?",
                total_cost,
                current_user_id,
            )

            # Check if user already owns the stock
            rows = db.execute(
                "SELECT shares FROM user_stocks WHERE user_id = ? AND symbol = ?",
                current_user_id,
                symbol,
            )
            if len(rows) == 1:
                # Update the shares if the user already owns the stock
                db.execute(
                    "UPDATE user_stocks SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                    shares,
                    current_user_id,
                    symbol,
                )
            else:
                # Insert new stock record if the user does not own the stock
                db.execute(
                    "INSERT INTO user_stocks (user_id, symbol, shares) VALUES (?, ?, ?)",
                    current_user_id,
                    symbol,
                    shares,
                )

            # Redirect to home page
            return redirect("/")

        except ValueError:
            return apology("Database error", 500)

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    current_user_id = session["user_id"]
    try:
        # TODO: get all transaction
        transactions = db.execute(
            "SELECT symbol, type, shares, price, transaction_time FROM transactions WHERE user_id = ?",
            current_user_id,
        )
        # print(transactions)
        return render_template("history.html", transactions=transactions)
    except ValueError:
        return apology("Database Error", 500)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        formUsername = request.form.get("username")
        formPassword = request.form.get("password")

        if not formUsername:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not formPassword:
            return apology("must provide password", 403)

        # if formUsername.isalnum():
        #     return apology("' and ; are not allowed", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", formUsername)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], formPassword):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        quote = request.form.get("symbol")

        if not quote:
            return apology("must provide quote")

        # if not quote.isupper() or len(quote) < 1 or len(quote) > 5:
        #     return apology("Invalid quote")

        quote = lookup(quote)

        if not quote:
            return apology("Invalid quote")

        # print(quote)

        return render_template("quoted.html", quote=quote)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # ensure username was submitted and valid
        if not username:
            return apology("must provide username", 400)

        # ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # ensure confirmation password was submitted
        elif not confirmation:
            return apology("must provide confirmation", 400)

        # ensure passwords match
        elif password != confirmation:
            return apology("passwords do not match", 400)

        # hash the user's password
        hash = generate_password_hash(password)

        # insert the new user into the database
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash
            )
        except ValueError:
            return apology("username already exists", 400)

        # redirect user to login page
        return redirect("/login")

    # render the registration form
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # extract current user id from session
    current_user_id = session["user_id"]

    # handle post request
    if request.method == "POST":
        # extract symbol and shares from form request
        sell_stock_symbol = request.form.get("symbol")
        sell_stock_shares = request.form.get("shares")
        # if not provide stock shares number
        if not sell_stock_shares:
            return apology("Invalid shares number")
        # if not a digit
        if not sell_stock_shares.isdigit():
            return apology("Invalid shares number")
        # convert stock shares number to int
        sell_stock_shares = int(sell_stock_shares)
        # if less than 1
        if sell_stock_shares < 1:
            return apology("Invalid shares number")

        # make sure user can sell (symbol exist, enough shares) by counting
        meet_conditions_count = db.execute(
            "SELECT COUNT(user_id) as n FROM user_stocks WHERE user_id = ? AND symbol = ? AND shares >= ?",
            current_user_id,
            sell_stock_symbol,
            sell_stock_shares,
        )
        if meet_conditions_count[0]["n"] > 0:
            # look up current stock price
            lookup_result = lookup(sell_stock_symbol)
            if not lookup_result:
                return apology("A Symbol Not Found", 404)
            cash_increase = lookup_result["price"] * sell_stock_shares
            try:
                # update user stock shares
                db.execute(
                    "UPDATE user_stocks SET shares = shares - ? WHERE user_id = ? AND symbol = ?",
                    sell_stock_shares,
                    current_user_id,
                    sell_stock_symbol,
                )
                # update user cash
                db.execute(
                    "UPDATE users SET cash = cash + ? WHERE id = ?",
                    cash_increase,
                    current_user_id,
                )
                # keep track of transactions
                db.execute(
                    "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
                    current_user_id,
                    sell_stock_symbol,
                    sell_stock_shares,
                    lookup_result["price"],
                    "sell",
                )
                return redirect("/")
            except ValueError:
                return apology("Database Error", 500)
        else:
            # apology user that cannot be done
            return apology("Cannot sell that stock")

    # handle get request
    try:
        user_stocks = db.execute(
            "SELECT symbol, shares FROM user_stocks WHERE user_id = ?", current_user_id
        )

        for stock in user_stocks:
            lookup_result = lookup(stock["symbol"])
            if not lookup_result:
                return apology("A Symbol Not Found", 404)
            stock["price"] = round(lookup_result["price"], 2)

        # print(user_stocks)
    except ValueError:
        return apology("Database Error", 500)
    return render_template("sell.html", user_stocks=user_stocks)


@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    """Show current user info"""
    current_user_id = session["user_id"]

    # allow user to add addtitional cash to their account
    if request.method == "POST":
        cash = request.form.get("cash")
        if not cash:
            return apology("Invalid cash number")
        if not cash.isdigit():
            return apology("Invalid cash number")
        cash = int(cash)
        # not allow withdraw
        if cash < 1:
            return apology("Invalid cash number")
        try:
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?", cash, current_user_id
            )
        except ValueError:
            return apology("Database Error", 500)
        return redirect("/profile")

    current_user_info = db.execute(
        "SELECT id, username, cash FROM users WHERE id = ?", current_user_id
    )
    # print(current_user_info)
    return render_template("profile.html", info=current_user_info[0])
