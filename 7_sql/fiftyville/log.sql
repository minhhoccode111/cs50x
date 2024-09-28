-- Keep a log of any SQL queries you execute as you solve the mystery.

-- people
-- flights
-- airports
-- interviews
-- passengers
-- phone_calls
-- bank_accounts
-- atm_transactions
-- crime_scene_reports
-- bakery_securtity_logs

-- schema
.schema

-- tables
.tables


-- find description about the crime reports
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time each of their interview transcripts mentions the bakery.

-- find transcript of the interview of 3 persons mentions bakery
SELECT id, name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- > 10:15 + 10 mins?

-- Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT *
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15 AND minute < 25;

-- > get who leaved the parking lot

-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+

SELECT *
FROM atm_transactions
WHERE month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';

-- > get who withdraw money

-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- | 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2023 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2023 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2023 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2023 | 7     | 28  | Leggett Street | withdraw         | 35     |

SELECT *
FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2023 AND duration < 60;

-- > get who called within 60 secs

-- | id  |     caller     |    receiver    | year | month | day | duration |
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2023 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2023 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2023 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2023 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2023 | 7     | 28  | 54       |

-- get the fiftyville airport
SELECT *
FROM airports
WHERE city = 'Fiftyville';

-- | id | abbreviation |          full_name          |    city    |
-- | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- > get Fiftyville id = 8

-- get the earliest flight
SELECT * 
FROM flights
WHERE month = 7 and day = 29 and year = 2023 and origin_airport_id = 8;

-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
-- > get destination id = 8
-- > get flight id = 36

-- get the destination airport
SELECT *
FROM airports
WHERE id = 8;

-- | id | abbreviation |     full_name     |     city      |
-- | 4  | LGA          | LaGuardia Airport | New York City |

SELECT * 
FROM passengers
WHERE flight_id = 36;

-- | flight_id | passport_number | seat |
-- | 36        | 7214083635      | 2A   |
-- | 36        | 1695452385      | 3B   |
-- | 36        | 5773159633      | 4A   |
-- | 36        | 1540955065      | 5C   |
-- | 36        | 8294398571      | 6C   |
-- | 36        | 1988161715      | 6D   |
-- | 36        | 9878712108      | 7A   |
-- | 36        | 8496433585      | 7B   |

-- get people that appear in 4 lists: phone caller, money withdraw, parking lot, passengers
SELECT * 
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE month = 7 AND day = 28 AND year = 2023 AND duration < 60
) AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
) AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15 AND minute < 25
) AND id IN (
    SELECT person_id 
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number 
        FROM atm_transactions
        WHERE month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street'
    )
);

-- > get the thief
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |

SELECT *
FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2023 AND duration < 60 AND caller = '(367) 555-5533';

-- > get the accomplice


-- | id  |     caller     |    receiver    | year | month | day | duration |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |

SELECT *
FROM people
WHERE phone_number = '(375) 555-8161';

-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |

