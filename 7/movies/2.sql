-- Executing 2.sql results in a table with 1 column and 1 row.

-- In 2.sql, write a SQL query to determine the birth year of Emma Stone.
-- Your query should output a table with a single column and a single row (not counting the header) containing Emma Stone’s birth year.
-- You may assume that there is only one person in the database with the name Emma Stone.

SELECT birth FROM people WHERE name = 'Emma Stone';
