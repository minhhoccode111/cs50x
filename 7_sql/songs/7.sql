select avg(energy) from songs where artist_id in (
select id from artists where name = 'Drake'
);
