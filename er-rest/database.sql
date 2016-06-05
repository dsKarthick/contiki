DROP DATABASE parking;
CREATE DATABASE IF NOT EXISTS parking;
USE parking;
CREATE TABLE sensors(
	sensorID varchar(255) NOT NULL UNIQUE,
	lat varchar(255),
	lon varchar(255),
	time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
	status int DEFAULT 0,
	PRIMARY KEY (sensorID)
);