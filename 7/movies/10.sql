-- Executing 10.sql results in a table with 1 column and 3,854 rows.

-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.
-- If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.

SELECT DISTINCT name FROM people WHERE people.id IN (
SELECT person_id FROM directors WHERE directors.movie_id IN (
        SELECT movie_id FROM ratings WHERE ratings.rating >= 9
    )
);

/* -- tweaking to check correctness
SELECT DISTINCT name, directors.title AS movie_title, directors.rating AS movie_rating FROM people 
JOIN ( -- DISTINCT not work because we don't have DISTINCT ON (name) name like PostgreSQL
SELECT person_id, movie_id, movies.title, movies.rating FROM directors 
    JOIN (
    SELECT title, year, id, ratings.rating FROM movies
        JOIN (
        SELECT movie_id, rating FROM ratings
            WHERE ratings.rating >= 9
        ) ratings
        ON ratings.movie_id = movies.id
    ) movies
    ON movies.id = directors.movie_id
) directors
ON directors.person_id = people.id
LIMIT 100; */


