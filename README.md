# University
 set @j = convert(LOAD_FILE('E:/Vano/proga/sql/poll_prop.json') using utf8mb4);
 
-- set @j='{"name": "Barney"}';
Insert into `poll`.`user` 
values (1, "Kravchuk", 'E:/Vano/proga/sql/picture/Kravchuk.png', "kravchuk@gmail.com"), 
	   (2, "Kuchma",'E:/Vano/proga/sql/picture/Kuchma.png',"kuchma@gmail.com");

insert into `poll`.`poll_prop` (`property1`) 
value(@j);
insert into `poll`.`poll_prop` (`property2`) 
select JSON_UNQUOTE(JSON_EXTRACT (@j, '$.name'));
insert into `poll`.`poll_prop` (`key`)
value(1) ;
