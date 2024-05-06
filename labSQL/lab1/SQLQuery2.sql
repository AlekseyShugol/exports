Use DreamHome
GO

ALTER TABLE PROPERTY
ADD CONSTRAINT FK_PROPERTY_Rooms CHECK (Rooms BETWEEN 1 AND 4)
GO

ALTER TABLE PROPERTY
ADD CONSTRAINT DEFAULT_PROPERTY_Ptel DEFAULT 'T' FOR Ptel
GO

CREATE INDEX idx_VIEWING_Date ON VIEWING(Date_View)
GO

CREATE INDEX idx_STAFF_FName ON STAFF(FName)
GO

CREATE INDEX idx_STAFF_Position ON STAFF(Position)
GO

CREATE TABLE BRANCH
(Branch_no member_no IDENTITY (1, 1) PRIMARY KEY,
Postcode postcode NULL,
City shortstring NOT NULL,
Street shortstring NOT NULL,
House nchar(10) NOT NULL,
Btel_no phonenumber NOT NULL,
Fax_no phonenumber NULL)
GO

CREATE TABLE OWNER
(Owner_no member_no IDENTITY (1, 1) NOT NULL,
FName shortstring	NOT NULL,
LName shortstring	NOT NULL,
City shortstring	NOT NULL,
Street shortstring	NOT NULL,
House nchar NOT NULL,
Flat smallint NULL,
Otel_no phonenumber	NULL)
GO

CREATE TABLE BUYER
(Buyer_no member_no NOT NULL PRIMARY KEY,
FName shortstring NOT NULL,
LName shortstring NOT NULL,
City shortstring NOT NULL,
Street shortstring NOT NULL,
House nchar(6) NOT NULL,
Flat smallint NULL,
Htel_no phonenumber NULL,
Wtel_no phonenumber NULL,
Prof_Rooms tinyint NOT NULL,
Max_Price money NOT NULL,
Branch_no member_no NOT NULL,
CONSTRAINT FK_BUYER_BRANCH FOREIGN KEY(Branch_no) REFERENCES BRANCH ON UPDATE CASCADE,
CHECK (Htel_no IS NOT NULL OR Wtel_no IS NOT NULL) 
)

ALTER TABLE BRANCH
DROP COLUMN Branch_no
GO

DROP TABLE BRANCH
GO
DROP TABLE BUYER
GO

INSERT INTO BRANCH (Postcode, City, Street, House, Btel_no, Fax_no) VALUES
('210009', 'Витебск', 'Замковая', '4/офис404',	'8(02122)37-73-56',	'37-73-58'),
('210033',	'Витебск',	'Суворова',	'9/11',	'8(02122)36-01-80',	'33-25-23'),
('211440',	'Новополоцк',	'Молодёжная',	'18',	'8(02144)57-31-29',	'57-25-30'),
('211460',	'Россоны',	'Ленина',	'3',	'8(02159)25-55-20', NULL)
GO

INSERT INTO OWNER (FName, LName, City, Street, House, Flat, Otel_no) VALUES
('Жерносек',	'Юрий',	'Витебск',	'Терешковой',	'28/1',	7,	'62-07-94'),
('Панкратова',	'Инна',	'Новополоцк',	'Парковая',	'2б',	12,	'57-12-48'),
('Амбражевич',	'Сергей',	'Новополоцк',	'Двинская',	'5',	18,	'52-14-89'),
('Поскрёбышева',	'Елена',	'Витебск',	'П.Бровки',	'26/1',	40, '23-00-72(аб978)'),
('Титов', 	'Николай',	'Витебск',	'Интернационалистов',	'35',	187,	'8(029)633-76-68'),
('Скребкова',	'Алла',	'Новополоцк',	'Молодёжная',	'1',	22,	'8(029)688-84-46'),
('Николаев',	'Влад',	'Витебск',	'Фрунзе',	'33',	214,	'8(029)673-07-30'),
('Цалко',	'Сергей',	'Лепель',	'Ленина', '14/2',	4, '25-17-90'),
('Цыркунова',	'Наталья',	'Россоны',	'Цветочная',	'90',	15,	'26-32-48'),
('Яковлев',	'Андрей',	'Витебск',	'Лазо',	'65', NULL,		'21-72-25')
GO
