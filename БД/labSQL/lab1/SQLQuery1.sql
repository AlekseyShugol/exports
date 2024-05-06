Use DreamHome
GO

create table STAFF 
(Staff_no varchar(9) NOT NULL PRIMARY KEY,
FName nvarchar(20) NOT NULL,
LName nvarchar(20) NOT NULL,
DOB datetime NOT NULL,
Sex char(1) NOT NULL,
City nvarchar(20) NOT NULL,
Street nvarchar(20) NOT NULL,
House char(3) NOT NULL,
Flat int NOT NULL,
Stel_no int NOT NULL,
Date_Joined datetime NOT NULL,
Position nvarchar(20) NOT NULL,
Salary int NOT NULL,
Branch_no int NULL)
GO

ALTER TABLE STAFF
ALTER COLUMN Date_Joined date NOT NULL
GO

ALTER TABLE STAFF
ALTER COLUMN Stel_no varchar(15) NULL
GO

ALTER TABLE STAFF
DROP FK_STAFF_Stel
GO

ALTER TABLE STAFF
ADD CONSTRAINT FK_STAFF_SEX CHECK (Sex = 'ì' OR Sex = 'æ' OR Sex = 'Ì' OR Sex = 'Æ')
GO

ALTER TABLE STAFF
ADD CONSTRAINT FK_STAFF_Stel_first CHECK
(Stel_no LIKE '8(029)[0-999]-[0-99]-[0-99]')
GO
ALTER TABLE STAFF
DROP FK_STAFF_Stel_first
GO

ALTER TABLE STAFF
ADD CONSTRAINT FK_STAFF_Stel_second CHECK
(Stel_no LIKE '[0-99]-[0-99]-[0-99]')
GO
ALTER TABLE STAFF
DROP FK_STAFF_Stel_second
GO