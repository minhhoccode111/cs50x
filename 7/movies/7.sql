-- Executing 7.sql results in a table with 2 columns and 7,192 rows.

-- In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
-- Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
-- Movies that do not have ratings should not be included in the result.

SELECT m.title, r.rating FROM movies m -- name movies to be m
JOIN ratings r -- name ratings to be r
ON m.id = r.movie_id
WHERE m.year = 2010 AND r.rating IS NOT NULL
ORDER BY r.rating DESC, m.title;
