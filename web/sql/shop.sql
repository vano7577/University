-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema poll
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `shop` ;

-- -----------------------------------------------------
-- Schema poll
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `shop` DEFAULT CHARACTER SET utf8 ;
USE `shop` ;
-- Use `user`;
DROP TABLE IF EXISTS `shop`.`order` ;
set @order_json = convert(LOAD_FILE('E:/Vano/proga/sql/web/order.json') using utf8mb4);
CREATE TABLE IF NOT EXISTS `shop`.`order` (
  `id` int not null AUTO_INCREMENT,
  `user_id` int NULL DEFAULT NULL,
    PRIMARY KEY (`id`),
  INDEX `fk_user_id1_idx` (`user_id` ASC) VISIBLE,
  CONSTRAINT `fk_user_id1`
    FOREIGN KEY (`user_id`)
    REFERENCES `user`.`user` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB select * from JSON_TABLE (
	@order_json,
    "$[*]"
    Columns(
	 `user_id` int path "$.id_user" ,
     `date` DATE  path "$.date",
     `delivery` varchar(90) path "$.delivery"
    )
) as t2;

select * from `shop`.`order`;

DROP TABLE IF EXISTS `shop`.`product` ;
set @product_json = convert(LOAD_FILE('E:/Vano/proga/sql/web/product.json') using utf8mb4);
CREATE TABLE IF NOT EXISTS `shop`.`product` (
  `id` int not null AUTO_INCREMENT,
      PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@product_json,
    "$[*]"
    Columns(
	 `name` varchar(255) path "$.name" ,
     `price` decimal(9,2)  path "$.price",
     `discount` float(5,3) path "$.discount",
     `picture` int path "$.picture"
    )
) as t3;

select * from `shop`.`product`;

-- -----------------------------------------------------
-- Table `shop`.`prod_order`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `shop`.`prod_order` ;
set @prod_order_json = convert(LOAD_FILE('E:/Vano/proga/sql/web/prod-order.json') using utf8mb4);
CREATE TABLE IF NOT EXISTS `shop`.`prod_order` (
  `product_id` INT NULL DEFAULT NULL,
  `order_id` INT NULL DEFAULT NULL,
  INDEX `fk_shop_product1_idx` (`product_id` ASC) VISIBLE,
  INDEX `fk_shop_order1_idx` (`order_id` ASC) VISIBLE,
  CONSTRAINT `fk_shop_product1`
    FOREIGN KEY (`product_id`)
    REFERENCES `shop`.`product` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_shop_order1`
    FOREIGN KEY (`order_id`)
    REFERENCES `shop`.`order` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB select * from JSON_TABLE (
	@prod_order_json,
    "$[*]"
    Columns(
     `product_id` int  path "$.id_product",
     `order_id` int path "$.id_order",
     `quantity` int path "$.quantity"
    )
) as t4;
select * from `shop`.`prod_order`;

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
