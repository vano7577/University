delimiter //
CREATE PROCEDURE routine2 (in num int)
BEGIN
select * from `shop`.`product`
where `product`.`id` in (select `prod_order`.`product_id` from `shop`.`prod_order` where `prod_order`.`order_id` = num);
END//
delimiter ;