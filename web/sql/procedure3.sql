delimiter //
CREATE PROCEDURE routine3 (in num int)
BEGIN
select * from `shop`.`product`
where `product`.`picture`  = num;
END//
delimiter ;