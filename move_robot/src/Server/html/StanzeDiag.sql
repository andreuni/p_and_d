-- Database: `StanzeDiag`


CREATE TABLE `Stanze` (
  `nome` varchar(100) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `theta` float NOT NULL,
  'log' int NOT NULL
);


INSERT INTO Stanze values -- ('nome','x','y','theta') VALUES
('aula1', 15.47, 9.75, 0.02, 0),
('aula2', 87.58, 9.72, 0.02, 0),
('aula3', 28.33, 8.96, 0.02, 0),
('aula4', 32.83, 9.53, 0.02, 0),
('aula5', 99.89, 19.18, 0.02, 0),
('aula6', 10.83, 10.18, 0.02, 0),
('aula7', 4.69, 21.81, 0.02, 0),
('aula_magna', 91.9, 9.72, 0.02, 0);


ALTER TABLE `Stanze`
  ADD PRIMARY KEY (`nome`);
COMMIT;
