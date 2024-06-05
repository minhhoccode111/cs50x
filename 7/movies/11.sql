-- Executing 11.sql results in a table with 1 column and 5 rows.

-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman.

-- nested query, so fast and performant but not ensure the order of movie's rating because only check if it's `IN` the previous nested query and not the sorted order

-- SELECT title FROM movies WHERE id IN (
--         SELECT movie_id FROM ratings WHERE movie_id IN (
--                 SELECT movie_id FROM stars WHERE person_id IN (
--                         SELECT id FROM people WHERE name = 'Chadwick Boseman'
--                 )
--         ) 
--         ORDER BY rating DESC
--         LIMIT 5
-- );

-- tweak with join to check correctness

-- SELECT movies.id AS movie_id, title AS movie_title, ratings.rating AS movie_rating, ratings.name AS star_name, ratings.id AS star_id FROM movies -- make sure things match and good
SELECT title FROM movies
JOIN (
        SELECT ratings.movie_id, stars.name, stars.id, rating FROM ratings
        JOIN (
                SELECT stars.movie_id, people.name, people.id FROM stars 
                JOIN (
                        SELECT id, name FROM people WHERE name = 'Chadwick Boseman'
                ) people
                ON people.id = person_id
        ) stars
        ON stars.movie_id = ratings.movie_id
        ORDER BY rating DESC
        LIMIT 5
) ratings
ON movies.id = ratings.movie_id;
