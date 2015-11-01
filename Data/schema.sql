
-- Not done
-- Complete later

--BEGIN TRANSACTION;
CREATE TABLE `users` (
	`user_id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`username`	TEXT NOT NULL UNIQUE,
	`fname`	TEXT NOT NULL,
	`lname`	TEXT NOT NULL,
	`type`	INTEGER NOT NULL,
	`ppp_id`	INTEGER,
	`date_created`	DATETIME DEFAULT CURRENT_TIMESTAMP,
	FOREIGN KEY(ppp_id) REFERENCES ppp(ppp_id)
);
CREATE TABLE `ppp` (
	`ppp_id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`bio` TEXT,
	`personal_tech_score` INTEGER,
	`we_bs` INTEGER,
	`teammate_tech_score` INTEGER
);
CREATE TABLE `qualification` (
	`qualification_id`	INTEGER PRIMARY KEY AUTOINCREMENT
);
CREATE TABLE `project_registration` (
	`project_id`	INTEGER NOT NULL,
	`user_id`	INTEGER NOT NULL,
	FOREIGN KEY(project_id) REFERENCES project(project_id)
	FOREIGN KEY(user_id) REFERENCES users(user_id)
	);
CREATE TABLE `project` (
	`project_id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`project_title`	TEXT NOT NULL,
	`project_description`	TEXT NOT NULL,
	`date_created`	DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE `ppp_qualifications` (
	`qualification_id`	INTEGER NOT NULL,
	`ppp_id`	INTEGER NOT NULL,
	`value`	INTEGER,
	FOREIGN KEY(ppp_id) REFERENCES ppp(ppp_id)
	FOREIGN KEY(qualification_id) REFERENCES qualification(qualification_id)
);
CREATE TABLE `project_configurations` (
	`config_id`	INTEGER NOT NULL,
	`project_id`	INTEGER NOT NULL,
	`value`	INTEGER NOT NULL,
	FOREIGN KEY(project_id) REFERENCES project(project_id)
	FOREIGN KEY(config_id) REFERENCES configurations(config_id)
);
CREATE TABLE `configurations` (
	`config_id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`text`	INTEGER NOT NULL,
	`value`	INTEGER NOT NULL
);
--COMMIT;
