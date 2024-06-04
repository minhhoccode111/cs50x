select name from songs where artist_id in (
select id from artists where name = 'Post Malone'
);
