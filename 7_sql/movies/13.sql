-- Executing 13.sql results in a table with 1 column and 182 rows.

-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.


SELECT name FROM people WHERE id IN ( -- get people name
        SELECT person_id FROM stars WHERE movie_id IN ( -- select people in movies with Bacon
                SELECT movie_id FROM stars WHERE person_id IN ( -- select movies with Bacon
                        SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958 -- select Bacon
                )
        )
)
AND name IS NOT 'Kevin Bacon' AND birth IS NOT 1958 -- not kevin bacon
;
