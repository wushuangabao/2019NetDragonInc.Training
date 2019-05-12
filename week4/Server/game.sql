/*
Navicat MySQL Data Transfer

Source Server         : test
Source Server Version : 50725
Source Host           : localhost:3306
Source Database       : game

Target Server Type    : MYSQL
Target Server Version : 50725
File Encoding         : 65001

Date: 2019-05-12 16:19:40
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for chat_record
-- ----------------------------
DROP TABLE IF EXISTS `chat_record`;
CREATE TABLE `chat_record` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime NOT NULL,
  `user_name` char(15) NOT NULL,
  `msg` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `user_chat` (`user_name`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of chat_record
-- ----------------------------
INSERT INTO `chat_record` VALUES ('1', '2019-05-07 13:59:43', 'admin', '兄弟们在吗？');
INSERT INTO `chat_record` VALUES ('2', '2019-05-07 16:09:45', 'admin', 'test');
INSERT INTO `chat_record` VALUES ('3', '2019-05-07 16:18:20', 'admin', '娴嬭瘯');
INSERT INTO `chat_record` VALUES ('4', '2019-05-07 16:23:46', 'admin', '娴嬭瘯');
INSERT INTO `chat_record` VALUES ('6', '2019-05-09 18:35:12', 'testUser', 'test');
INSERT INTO `chat_record` VALUES ('7', '2019-05-09 20:29:14', 'testUser', 'aaa');
INSERT INTO `chat_record` VALUES ('8', '2019-05-09 20:30:03', 'testUser', 'aaa');
INSERT INTO `chat_record` VALUES ('9', '2019-05-09 20:45:54', 'testUser', 'aaa');
INSERT INTO `chat_record` VALUES ('10', '2019-05-09 20:46:30', 'testUser', 'aaa');
INSERT INTO `chat_record` VALUES ('11', '2019-05-09 20:48:33', 'testUser', 'aaa');
INSERT INTO `chat_record` VALUES ('12', '2019-05-09 20:54:16', 'test', 'aaa');
INSERT INTO `chat_record` VALUES ('13', '2019-05-12 14:43:29', 'testUser', '123');
INSERT INTO `chat_record` VALUES ('14', '2019-05-12 15:00:16', 'testUser', '123');
INSERT INTO `chat_record` VALUES ('15', '2019-05-12 15:11:07', 'testUser', '111');
INSERT INTO `chat_record` VALUES ('16', '2019-05-12 15:38:33', 'testUser', 'fds');
INSERT INTO `chat_record` VALUES ('17', '2019-05-12 15:38:40', 'testUser', 'dsada');

-- ----------------------------
-- Table structure for manipulate
-- ----------------------------
DROP TABLE IF EXISTS `manipulate`;
CREATE TABLE `manipulate` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `user_name` char(15) NOT NULL,
  `move_x` float NOT NULL,
  `move_y` float NOT NULL,
  `move_z` float NOT NULL,
  `crouch` tinyint(1) NOT NULL,
  `jump` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `user_manipulate` (`user_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of manipulate
-- ----------------------------

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `user_name` char(15) NOT NULL,
  `pass_word` char(31) NOT NULL,
  PRIMARY KEY (`user_name`),
  UNIQUE KEY `user_name` (`user_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('admin', '123456');
INSERT INTO `user` VALUES ('test', '111111');
