delimiter //
CREATE PROCEDURE routine1 (in num int)
BEGIN
select * from `shop`.`order`
where `order`.`user_id`= num;
END//
delimiter ;