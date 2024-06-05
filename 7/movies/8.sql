-- Executing 8.sql results in a table with 1 column and 4 rows.

-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.

-- nested query 
-- fast 0.1s but only display 1 column

SELECT name FROM people
WHERE id IN (
SELECT person_id FROM stars
    WHERE movie_id IN (
    SELECT id FROM movies
        WHERE title = 'Toy Story'
    )
);

-- join query 
-- super slow 1.6s but can display another column if wanted

/* SELECT name--, s.title -- include title which return from () s
FROM people
JOIN (
SELECT person_id, movie_id--, m.title -- have to return title which return from () m
    FROM stars
    JOIN (
    SELECT id--, title -- return title
        FROM movies
        WHERE title = 'Toy Story'
    ) m
    ON movie_id = m.id
) s
ON id = s.person_id; */

