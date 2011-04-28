-- phpMyAdmin SQL Dump
-- version 2.8.2.4
-- http://www.phpmyadmin.net
-- 
-- Host: localhost:3306
-- Generation Time: Feb 12, 2009 at 08:55 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.6
-- 
-- Database: `vulab_vulab`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `access`
-- 

CREATE TABLE `access` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `survey_id` int(10) unsigned NOT NULL default '0',
  `realm` char(16) default NULL,
  `maxlogin` int(10) unsigned default '0',
  `resume` enum('Y','N') NOT NULL default 'N',
  `navigate` enum('Y','N') NOT NULL default 'N',
  PRIMARY KEY  (`id`),
  KEY `survey_id` (`survey_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `conditions`
-- 

CREATE TABLE `conditions` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `survey_id` int(10) unsigned NOT NULL default '0',
  `q1_id` int(10) unsigned NOT NULL default '0',
  `q2_id` int(10) unsigned NOT NULL default '0',
  `cond` int(10) unsigned NOT NULL default '0',
  `cond_value` text,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `designer`
-- 

CREATE TABLE `designer` (
  `username` char(64) NOT NULL default '',
  `password` char(64) NOT NULL default '',
  `auth` char(16) NOT NULL default 'BASIC',
  `realm` char(16) NOT NULL default '',
  `fname` char(16) default NULL,
  `lname` char(24) default NULL,
  `email` char(64) default NULL,
  `pdesign` enum('Y','N') NOT NULL default 'Y',
  `pstatus` enum('Y','N') NOT NULL default 'N',
  `pdata` enum('Y','N') NOT NULL default 'N',
  `pall` enum('Y','N') NOT NULL default 'N',
  `pgroup` enum('Y','N') NOT NULL default 'N',
  `puser` enum('Y','N') NOT NULL default 'N',
  `disabled` enum('Y','N') NOT NULL default 'N',
  `changed` timestamp NOT NULL default '0000-00-00 00:00:00',
  `expiration` timestamp NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`username`,`realm`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `project`
-- 

CREATE TABLE `project` (
  `id` bigint(20) unsigned NOT NULL auto_increment COMMENT 'primary key of project table',
  `name` varchar(40) NOT NULL default '' COMMENT 'name of the project',
  `presurvey` bigint(20) unsigned default NULL COMMENT 'id of presurvey',
  `postsurvey` bigint(20) unsigned default NULL COMMENT 'id of postsurvey',
  `action_intro_msg` text COMMENT 'message to display before action',
  `action_outro_msg` text COMMENT 'message to display after action',
  `goal` varchar(999) NOT NULL,
  `action_url` varchar(255) default NULL COMMENT 'url of action to test',
  `start` text NOT NULL,
  `end` varchar(99) NOT NULL default '',
  `status` varchar(10) NOT NULL default '',
  `createstamp` varchar(99) NOT NULL default '',
  `editstamp` varchar(99) NOT NULL default '',
  `activestamp` varchar(99) NOT NULL default '',
  `completestamp` varchar(99) NOT NULL default '',
  `pre_source` varchar(99) NOT NULL default '',
  `post_source` varchar(99) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=93 DEFAULT CHARSET=latin1 AUTO_INCREMENT=93 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `question`
-- 

CREATE TABLE `question` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `survey_id` int(10) unsigned NOT NULL default '0',
  `name` varchar(30) NOT NULL default '',
  `type_id` int(10) unsigned NOT NULL default '0',
  `result_id` int(10) unsigned default NULL,
  `length` int(11) NOT NULL default '0',
  `precise` int(11) NOT NULL default '0',
  `position` int(10) unsigned NOT NULL default '0',
  `content` text NOT NULL,
  `required` enum('Y','N') NOT NULL default 'N',
  `deleted` enum('Y','N') NOT NULL default 'N',
  `public` enum('Y','N') NOT NULL default 'Y',
  PRIMARY KEY  (`id`),
  KEY `result_id` (`result_id`),
  KEY `survey_id` (`survey_id`)
) ENGINE=MyISAM AUTO_INCREMENT=141 DEFAULT CHARSET=latin1 AUTO_INCREMENT=141 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `question_choice`
-- 

CREATE TABLE `question_choice` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `question_id` int(10) unsigned NOT NULL default '0',
  `content` text NOT NULL,
  `value` text,
  PRIMARY KEY  (`id`),
  KEY `question_id` (`question_id`)
) ENGINE=MyISAM AUTO_INCREMENT=266 DEFAULT CHARSET=latin1 AUTO_INCREMENT=266 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `question_type`
-- 

CREATE TABLE `question_type` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `type` char(32) NOT NULL default '',
  `has_choices` enum('Y','N') NOT NULL default 'Y',
  `response_table` char(32) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=101 DEFAULT CHARSET=latin1 AUTO_INCREMENT=101 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `realm`
-- 

CREATE TABLE `realm` (
  `name` char(16) NOT NULL default '',
  `title` char(64) NOT NULL default '',
  `changed` timestamp NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `respondent`
-- 

CREATE TABLE `respondent` (
  `username` char(64) NOT NULL default '',
  `password` char(64) NOT NULL default '',
  `auth` char(16) NOT NULL default 'BASIC',
  `realm` char(16) NOT NULL default '',
  `fname` char(16) default NULL,
  `lname` char(24) default NULL,
  `email` char(64) default NULL,
  `disabled` enum('Y','N') NOT NULL default 'N',
  `changed` timestamp NOT NULL default '0000-00-00 00:00:00',
  `expiration` timestamp NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`username`,`realm`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `response`
-- 

CREATE TABLE `response` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `survey_id` int(10) unsigned NOT NULL default '0',
  `submitted` timestamp NOT NULL default '0000-00-00 00:00:00',
  `complete` enum('Y','N') NOT NULL default 'N',
  `username` varchar(64) default NULL,
  `ip` varchar(64) default NULL,
  `vid` varchar(99) NOT NULL default '',
  PRIMARY KEY  (`id`),
  KEY `survey_id` (`survey_id`)
) ENGINE=MyISAM AUTO_INCREMENT=258 DEFAULT CHARSET=latin1 AUTO_INCREMENT=258 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_bool`
-- 

CREATE TABLE `response_bool` (
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `choice_id` enum('Y','N') NOT NULL default 'Y',
  PRIMARY KEY  (`response_id`,`question_id`),
  KEY `response_id` (`response_id`),
  KEY `question_id` (`question_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_date`
-- 

CREATE TABLE `response_date` (
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `response` date default NULL,
  PRIMARY KEY  (`response_id`,`question_id`),
  KEY `response_id` (`response_id`),
  KEY `question_id` (`question_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_multiple`
-- 

CREATE TABLE `response_multiple` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `choice_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `response_id` (`response_id`),
  KEY `question_id` (`question_id`),
  KEY `choice_id` (`choice_id`)
) ENGINE=MyISAM AUTO_INCREMENT=22 DEFAULT CHARSET=latin1 AUTO_INCREMENT=22 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_other`
-- 

CREATE TABLE `response_other` (
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `choice_id` int(10) unsigned NOT NULL default '0',
  `response` text,
  PRIMARY KEY  (`response_id`,`question_id`,`choice_id`),
  KEY `response_id` (`response_id`),
  KEY `choice_id` (`choice_id`),
  KEY `question_id` (`question_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_rank`
-- 

CREATE TABLE `response_rank` (
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `choice_id` int(10) unsigned NOT NULL default '0',
  `rank` int(11) NOT NULL default '0',
  PRIMARY KEY  (`response_id`,`question_id`,`choice_id`),
  KEY `response_id` (`response_id`),
  KEY `question_id` (`question_id`),
  KEY `choice_id` (`choice_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_single`
-- 

CREATE TABLE `response_single` (
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `choice_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`response_id`,`question_id`),
  KEY `response_id` (`response_id`),
  KEY `question_id` (`question_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `response_text`
-- 

CREATE TABLE `response_text` (
  `response_id` int(10) unsigned NOT NULL default '0',
  `question_id` int(10) unsigned NOT NULL default '0',
  `response` text,
  PRIMARY KEY  (`response_id`,`question_id`),
  KEY `response_id` (`response_id`),
  KEY `question_id` (`question_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `survey`
-- 

CREATE TABLE `survey` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(64) NOT NULL default '',
  `owner` varchar(16) NOT NULL default '',
  `realm` varchar(64) NOT NULL default '',
  `public` enum('Y','N') NOT NULL default 'Y',
  `status` int(10) unsigned NOT NULL default '0',
  `title` varchar(255) NOT NULL default '',
  `email` varchar(64) default NULL,
  `subtitle` text,
  `info` text,
  `theme` varchar(64) default NULL,
  `thanks_page` varchar(255) default NULL,
  `thank_head` varchar(255) default NULL,
  `thank_body` text,
  `changed` timestamp NOT NULL default '0000-00-00 00:00:00',
  `auto_num` enum('Y','N') NOT NULL default 'Y',
  `userid` bigint(20) unsigned default NULL,
  `pid` varchar(99) NOT NULL default '',
  `history` varchar(99) NOT NULL default '',
  `PublicSurvey` enum('Y','N') NOT NULL default 'N'
  PRIMARY KEY  (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=197 DEFAULT CHARSET=latin1 AUTO_INCREMENT=197 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `user`
-- 

CREATE TABLE `user` (
  `userid` bigint(20) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `password` char(64) NOT NULL default '',
  `fname` char(64) default NULL,
  `lname` char(64) default NULL,
  `email` char(64) NOT NULL default '',
  `isresearcher` enum('Y','N') NOT NULL default 'N',
  `disabled` enum('Y','N') NOT NULL default 'N',
  PRIMARY KEY  (`userid`)
) ENGINE=MyISAM AUTO_INCREMENT=45 DEFAULT CHARSET=latin1 AUTO_INCREMENT=45 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `userprojectrel`
-- 

CREATE TABLE `userprojectrel` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `userid` bigint(20) unsigned NOT NULL default '0',
  `projectid` bigint(20) unsigned NOT NULL default '0',
  `admin` enum('Y','N') NOT NULL default 'N',
  PRIMARY KEY  (`id`),
  KEY `one_rel` (`userid`,`projectid`)
) ENGINE=MyISAM AUTO_INCREMENT=205 DEFAULT CHARSET=latin1 AUTO_INCREMENT=205 ;


INSERT INTO realm (name, title, changed) VALUES ('superuser', 'ESP System Administrators', '0000-00-00 00:00:00'),
('auto', 'Self added users', '0000-00-00 00:00:00');

-- # populate the types of questions
INSERT INTO question_type VALUES ('1','Yes/No','N','response_bool');
INSERT INTO question_type VALUES ('2','Text Box','N','response_text');
INSERT INTO question_type VALUES ('3','Essay Box','N','response_text');
INSERT INTO question_type VALUES ('4','Radio Buttons','Y','response_single');
INSERT INTO question_type VALUES ('5','Check Boxes','Y','response_multiple');
INSERT INTO question_type VALUES ('6','Dropdown Box','Y','response_single');
-- # INSERT INTO question_type VALUES ('7','Rating','N','response_rank');
INSERT INTO question_type VALUES ('8','Rate (scale 1..5)','Y','response_rank');
INSERT INTO question_type VALUES ('9','Date','N','response_date');
INSERT INTO question_type VALUES ('10','Numeric','N','response_text');
INSERT INTO question_type VALUES ('99','Page Break','N','');
INSERT INTO question_type VALUES ('100','Section Text','N','');