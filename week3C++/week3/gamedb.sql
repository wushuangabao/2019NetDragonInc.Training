/*
 Navicat Premium Data Transfer
 Source Server         : testdb
 Source Server Type    : MySQL
 Source Server Version : 50714
 Source Host           : localhost:3306
 Source Schema         : gamedb
 Target Server Type    : MySQL
 Target Server Version : 50714
 File Encoding         : 65001
 Date: 22/06/2018 15:40:35
*/

CREATE DATABASE gamedb;
USE gamedb;

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;


DROP TABLE IF EXISTS `actor`;
CREATE TABLE `actor`  (
  `name` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT 'people\'s name',
  PRIMARY KEY (`name`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;


INSERT INTO `actor` VALUES ('关羽', NULL);
INSERT INTO `actor` VALUES ('嬴政', NULL);
INSERT INTO `actor` VALUES ('宙斯', 'Bob');
INSERT INTO `actor` VALUES ('温蒂', 'Anne');
INSERT INTO `actor` VALUES ('猎魔人', 'Jane');
INSERT INTO `actor` VALUES ('石甲守护者', NULL);
INSERT INTO `actor` VALUES ('风暴之灵', NULL);


DROP TABLE IF EXISTS `msg`;
CREATE TABLE `msg`  (
  `id` int(8) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `name` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `text` tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `time` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 5 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;


INSERT INTO `msg` VALUES (1, 'Anne', '温蒂', '全军出鸡！', '2018-06-20 09:00:05');
INSERT INTO `msg` VALUES (2, 'Anne', '温蒂', '欢迎来到英魂之刃1', '2018-06-21 14:59:08');

DROP TABLE IF EXISTS `people`;
CREATE TABLE `people`  (
  `name` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `passwd` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sex` tinyint(1) NULL DEFAULT NULL,
  PRIMARY KEY (`name`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;


INSERT INTO `people` VALUES ('Anne', '12345', NULL);
INSERT INTO `people` VALUES ('Bob', '666666', 1);
INSERT INTO `people` VALUES ('Jack', 'jack', 1);
INSERT INTO `people` VALUES ('Jane', 'jjj123456', 0);

SET FOREIGN_KEY_CHECKS = 1;