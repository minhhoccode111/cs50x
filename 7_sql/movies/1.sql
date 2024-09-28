-- Executing 1.sql results in a table with 1 column and 10,276 rows.

-- In 1.sql, write a SQL query to list the titles of all movies released in 2008.
-- Your query should output a table with a single column for the title of each movie.

SELECT title FROM movies WHERE year = 2008;
