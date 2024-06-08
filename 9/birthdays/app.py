import os

from cs50 import SQL
from flask import (Flask, flash, jsonify, redirect, render_template, request,
                   session)

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def is_valid_month(month):
    # Check if the string is a non-zero digit
    if month.isdigit():
        month = int(month)
        if 1 <= month <= 12:
            return True
    return False

def is_valid_day(day, month):
    # Check if the string is a non-zero digit
    if day.isdigit():
        day = int(day)
        # Handle the maximum number of days based on the month
        if month in [1, 3, 5, 7, 8, 10, 12]:
            max_days = 31
        elif month == 2:
            max_days = 29  # Assuming a leap year for simplicity
        else:
            max_days = 30

        if 1 <= day <= max_days:
            return True
    return False


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # Validate submission
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # if name is none, or all spaces
        if not name or name.isspace():
            return redirect("/error?q=name")

        # if month is none or not an integer or not valid month value
        if not month or not is_valid_month(month):
            return redirect("/error?q=month")

        if not day or not is_valid_day(day, int(month)):
            return redirect("/error?q=day")

        try:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, int(month), int(day))
        except Exception as e:
            return redirect("/error?q=database")

        return redirect("/")

    # else
    birthdays = db.execute("SELECT name, month, day FROM birthdays")
    return render_template("index.html", birthdays = birthdays)


@app.route("/error")
def error():
    query_param = request.args.get("q")
    error_message = "Unknown error"

    if query_param == "name":
        error_message = "Invalid Name"
    elif query_param == "month":
        error_message = "Invalid Month"
    elif query_param == "day":
        error_message = "Invalid Day"
    elif query_param == "database":
        error_message = "Database Error"

    return render_template('error.html', error = error_message)
