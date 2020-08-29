SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

set @user_json = convert(LOAD_FILE('/home/vano/proga/sql/user.json') using utf8mb4);
set @poll_json = convert(LOAD_FILE('/home/vano/proga/sql/poll.json') using utf8mb4);
set @prop_json = convert(LOAD_FILE('/home/vano/proga/sql/prop.json') using utf8mb4);
set @poll_include_json = convert(LOAD_FILE('/home/vano/proga/sql/poll_include.json') using utf8mb4);
set @session_json = convert(LOAD_FILE('/home/vano/proga/sql/session.json') using utf8mb4);
set @question_json = convert(LOAD_FILE('/home/vano/proga/sql/question.json') using utf8mb4);
set @response_json = convert(LOAD_FILE('/home/vano/proga/sql/response.json') using utf8mb4);
set @response_prop_json = convert(LOAD_FILE('/home/vano/proga/sql/response_prop.json') using utf8mb4);
set @alternative_json = convert(LOAD_FILE('/home/vano/proga/sql/alternative.json') using utf8mb4);
set @alternative_prop_json = convert(LOAD_FILE('/home/vano/proga/sql/alternative_prop.json') using utf8mb4);
set @question_prop_json = convert(LOAD_FILE('/home/vano/proga/sql/question_prop.json') using utf8mb4);

-- -----------------------------------------------------
-- Schema poll
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `poll` ;

-- -----------------------------------------------------
-- Schema poll
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `poll` DEFAULT CHARACTER SET utf8 ;
USE `poll` ;

-- -----------------------------------------------------
-- Table `poll`.`user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`user` ;

CREATE TABLE IF NOT EXISTS `poll`.`user` (
  `id` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@user_json,
    "$[*]"
    Columns(
     `name` varchar(255)  path "$.name",
     `photo` varchar(255) path "$.photo",
     `email` varchar(255) path "$.email"
    )
) as t1;

select * from `poll`.`user`;
-- -----------------------------------------------------
-- Table `poll`.`poll`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`poll` ;

CREATE TABLE IF NOT EXISTS `poll`.`poll` (
  `id` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@poll_json,
    "$[*]"
    Columns(
     `name` varchar(255)  path "$.name"
    )
) as t2;

select * from `poll`.`poll`;
-- -----------------------------------------------------
-- Table `poll`.`poll_prop`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`prop` ;

CREATE TABLE IF NOT EXISTS `poll`.`prop` (
  `poll_id` int NULL DEFAULT NULL
    )
ENGINE = InnoDB select * from JSON_TABLE (
	@prop_json,
    "$[*]"
    Columns(
     `report` varchar(255)  path "$.report"
    )
) as t3;

ALTER TABLE `poll`.`prop` 
  MODIFY `poll_id` int NULL DEFAULT NULL AUTO_INCREMENT,
  ADD FOREIGN KEY (`poll_id`)
      REFERENCES `poll`.`poll` (`id`);

select * from `poll`.`prop`;
-- -----------------------------------------------------
-- Table `poll`.`include`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`include` ;

CREATE TABLE IF NOT EXISTS `poll`.`include` (
  `poll_id_to` INT NULL DEFAULT NULL
)
ENGINE = InnoDB select * from JSON_TABLE (
	@poll_include_json,
    "$[*]"
    Columns(
     `poll_id_from` int  path "$.from",
     `poll_id_to` int path "$.to"
    )
) as t4;

ALTER TABLE `poll`.`include`
ADD FOREIGN KEY (`poll_id_from`)
    REFERENCES `poll`.`poll` (`id`),
ADD FOREIGN KEY (`poll_id_to`)
    REFERENCES `poll`.`poll` (`id`);
select * from `poll`.`include`;
-- -----------------------------------------------------
-- Table `poll`.`session`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`session` ;

CREATE TABLE IF NOT EXISTS `poll`.`session` (
  `id` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@session_json,
    "$[*]"
    Columns(
     `user_id` int  path "$.user_id",
     `poll_id` int path "$.poll_id",
     `start` DATETIME path "$.start",
     `end` DATETIME path "$.end"
    )
) as t5;

ALTER TABLE `poll`.`session`
ADD FOREIGN KEY (`user_id`)
    REFERENCES `poll`.`user` (`id`),
ADD FOREIGN KEY (`poll_id`)
    REFERENCES `poll`.`poll` (`id`);

select * from `poll`.`session`;
-- -----------------------------------------------------
-- Table `poll`.`question`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`question` ;

CREATE TABLE IF NOT EXISTS `poll`.`question` (
  `id` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@question_json,
    "$[*]"
    Columns(
     `poll_id` int  path "$.k"
    )
) as t6;

ALTER TABLE `poll`.`question`
ADD FOREIGN KEY (`poll_id`)
    REFERENCES `poll`.`poll` (`id`);

select * from `poll`.`question`;
-- -----------------------------------------------------
-- Table `poll`.`responce`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`response` ;

CREATE TABLE IF NOT EXISTS `poll`.`response` (
  `id` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@response_json,
    "$[*]"
    Columns(
     `session_id` int  path "$.session_id",
     `question_id` int path "$.question_id"
    )
) as t7;

ALTER TABLE `poll`.`response`
ADD FOREIGN KEY (`session_id`)
    REFERENCES `poll`.`session` (`id`),
ADD     FOREIGN KEY (`question_id`)
    REFERENCES `poll`.`question` (`id`);

select * from `poll`.`response`;
-- -----------------------------------------------------
-- Table `poll`.`response_prop`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`response_prop` ;

CREATE TABLE IF NOT EXISTS `poll`.`response_prop` (
  `response_id` INT NULL )
ENGINE = InnoDB select * from JSON_TABLE (
	@response_prop_json,
    "$[*]"
    Columns(
     `action` varchar(255)  path "$.action"
    )
) as t8;

ALTER TABLE `poll`.`response_prop`
  MODIFY `response_id` int NULL DEFAULT NULL AUTO_INCREMENT,
  ADD FOREIGN KEY (`response_id`)
      REFERENCES `poll`.`response` (`id`);

select * from `poll`.`response_prop`;
-- -----------------------------------------------------
-- Table `poll`.`alternative`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`alternative` ;

CREATE TABLE IF NOT EXISTS `poll`.`alternative` (
  `id` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`))
ENGINE = InnoDB select * from JSON_TABLE (
	@alternative_json,
    "$[*]"
    Columns(
     `question_id` int  path "$.k"
    )
) as t9;

ALTER TABLE `poll`.`alternative`    
    ADD FOREIGN KEY (`question_id`)
    REFERENCES `poll`.`question` (`id`);
    
select * from `poll`.`alternative` order by id;

-- -----------------------------------------------------
-- Table `poll`.`alternative_prop`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`alternative_prop` ;

CREATE TABLE IF NOT EXISTS `poll`.`alternative_prop` (
  `alternative_id` INT NULL DEFAULT NULL)
ENGINE = InnoDB select * from JSON_TABLE (
	@alternative_prop_json,
    "$[*]"
    Columns(
     `value_int` int path "$.value",
	   `value_date` DATE path "$.value",
     `value_str` varchar(255)  path "$.value",
     `type.isAuthorAnswer` bool path "$.type.isAuthorAnswer", 
     `type.isSingleChoise` bool path "$.type.isSingleChoise"
    )
) as t10;

ALTER TABLE `poll`.`alternative_prop`
  MODIFY `alternative_id` int NULL DEFAULT NULL AUTO_INCREMENT,
  ADD FOREIGN KEY (`alternative_id`)
      REFERENCES `poll`.`alternative` (`id`);

select * from `poll`.`alternative_prop`;
-- -----------------------------------------------------
-- Table `poll`.`question_prop`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `poll`.`question_prop` ;

CREATE TABLE IF NOT EXISTS `poll`.`question_prop` (
  `question_id` INT NULL DEFAULT NULL)
ENGINE = InnoDB select * from JSON_TABLE (
	@question_prop_json,
    "$[*]"
    Columns(
     `value_str` varchar(255)  path "$.value",
     `type.isOligatory` bool path "$.type.isOligatory"
    )
) as t11;

ALTER TABLE `poll`.`question_prop`
  MODIFY `question_id` int NULL DEFAULT NULL AUTO_INCREMENT,
  ADD FOREIGN KEY (`question_id`)
      REFERENCES `poll`.`question` (`id`);

select * from `poll`.`question_prop`;

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;