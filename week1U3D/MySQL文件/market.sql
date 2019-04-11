/*
Navicat MySQL Data Transfer

Source Server         : test
Source Server Version : 50505
Source Host           : localhost:3306
Source Database       : market

Target Server Type    : MYSQL
Target Server Version : 50505
File Encoding         : 65001

Date: 2019-04-11 14:10:15
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for goods
-- ----------------------------
DROP TABLE IF EXISTS `goods`;
CREATE TABLE `goods` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(63) NOT NULL,
  `type` varchar(63) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `unit` varchar(7) NOT NULL,
  `count` int(255) unsigned zerofill NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`),
  KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of goods
-- ----------------------------
INSERT INTO `goods` VALUES ('1', '肥皂', '生活用品', '5.00', '块', '1');
INSERT INTO `goods` VALUES ('2', '袜子', '生活用品', '8.00', '双', '0');
INSERT INTO `goods` VALUES ('3', '内裤', '生活用品', '20.00', '条', '0');

-- ----------------------------
-- Table structure for goods_store
-- ----------------------------
DROP TABLE IF EXISTS `goods_store`;
CREATE TABLE `goods_store` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `goods` int(255) unsigned NOT NULL,
  `warehouse` int(15) unsigned NOT NULL,
  `shelf` int(15) unsigned NOT NULL,
  `shelf_storey` int(7) unsigned NOT NULL,
  `count` int(127) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 COMMENT='这张表记录：商品出入库操作\r\nshelf_storey：货架的第几层\r\ncount：增加的商品数量，正数表示入库，负数表示出库。';

-- ----------------------------
-- Records of goods_store
-- ----------------------------
INSERT INTO `goods_store` VALUES ('1', '1', '1', '1', '2', '1');
INSERT INTO `goods_store` VALUES ('2', '1', '1', '1', '2', '1');
INSERT INTO `goods_store` VALUES ('3', '1', '1', '1', '2', '-1');

-- ----------------------------
-- Table structure for shelves
-- ----------------------------
DROP TABLE IF EXISTS `shelves`;
CREATE TABLE `shelves` (
  `id` int(15) unsigned NOT NULL AUTO_INCREMENT,
  `count` tinyint(7) unsigned NOT NULL DEFAULT '1',
  `warehouse` int(15) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`),
  KEY `warehouse` (`warehouse`),
  CONSTRAINT `shelves_ibfk_1` FOREIGN KEY (`warehouse`) REFERENCES `warehouse` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8 COMMENT='count表示货架有几层；\r\nwarehouse表示货架所在仓库的id。';

-- ----------------------------
-- Records of shelves
-- ----------------------------
INSERT INTO `shelves` VALUES ('1', '7', '1');
INSERT INTO `shelves` VALUES ('2', '7', '1');
INSERT INTO `shelves` VALUES ('3', '6', '2');

-- ----------------------------
-- Table structure for warehouse
-- ----------------------------
DROP TABLE IF EXISTS `warehouse`;
CREATE TABLE `warehouse` (
  `id` int(15) unsigned NOT NULL AUTO_INCREMENT,
  `address` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of warehouse
-- ----------------------------
INSERT INTO `warehouse` VALUES ('1', '北京市朝阳区');
INSERT INTO `warehouse` VALUES ('2', '杭州市萧山区');
