-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               10.1.34-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win32
-- HeidiSQL Version:             9.5.0.5196
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Dumping database structure for logs
CREATE DATABASE IF NOT EXISTS `logs` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `logs`;

-- Dumping structure for table logs.all_logs
CREATE TABLE IF NOT EXISTS `all_logs` (
  `Log_index` int(10) NOT NULL,
  `Log_action` varchar(65) NOT NULL,
  `Reader_ID` int(10) NOT NULL,
  `Card_ID` int(10) NOT NULL,
  `System_ID` int(10) NOT NULL,
  `NFC_UID` varchar(20) NOT NULL,
  `UID_Length` int(10) NOT NULL,
  `Timestamp` varchar(65) NOT NULL,
  `RorL` varchar(10) NOT NULL,
  PRIMARY KEY (`Log_index`,`Reader_ID`,`Timestamp`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Data exporting was unselected.
-- Dumping structure for table logs.blacklist
CREATE TABLE IF NOT EXISTS `blacklist` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `CardID` varchar(20) NOT NULL,
  `ReaderID` int(5) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Data exporting was unselected.
-- Dumping structure for table logs.whitelist
CREATE TABLE IF NOT EXISTS `whitelist` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Uid` varchar(20) NOT NULL,
  `ReaderID` int(5) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- Data exporting was unselected.
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
