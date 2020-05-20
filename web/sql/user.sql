-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema shop
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `user` ;

CREATE SCHEMA IF NOT EXISTS `user` DEFAULT CHARACTER SET utf8 ;
USE `user` ;


-- -----------------------------------------------------
-- Table `user`.`user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `user`.`user` ;
set @user_json = convert(LOAD_FILE('E:/Vano/proga/sql/web/user.json') using utf8mb4);

CREATE TABLE IF NOT EXISTS `user`.`user` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `id_shop` int Null default 1,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@user_json,
    "$[*]"
    Columns(
     `email` varchar(255)  path "$.email",
     `date_registr` DATE path "$.date_registr",
     `tel` bigint(12) path "$.tel"
    )
) as t1;

select * from `user`.`user`;
SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
