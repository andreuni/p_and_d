-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Jun 01, 2021 at 02:16 PM
-- Server version: 10.4.18-MariaDB
-- PHP Version: 8.0.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `StanzeDiag`
--

-- --------------------------------------------------------

--
-- Table structure for table `Stanze`
--

CREATE TABLE `Stanze` (
  `nome` varchar(100) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `theta` float NOT NULL,
  'log' int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `Stanze`
--

INSERT INTO Stanze values -- ('nome','x','y','theta') VALUES
('aula1', 15.47, 9.75, 0.02, 0),
('aula2', 87.58, 9.72, 0.02, 0),
('aula3', 28.33, 8.96, 0.02, 0),
('aula4', 32.83, 9.53, 0.02, 0),
('aula5', 99.89, 19.18, 0.02, 0),
('aula6', 10.83, 10.18, 0.02, 0),
('aula7', 4.69, 21.81, 0.02, 0),
('aula_magna', 91.9, 9.72, 0.02, 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Stanze`
--
ALTER TABLE `Stanze`
  ADD PRIMARY KEY (`nome`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
