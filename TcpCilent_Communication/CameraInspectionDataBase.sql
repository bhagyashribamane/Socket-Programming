create database Camera_Inspection;

use Camera_Inspection;
show tables; 

create table Jobdetails(
JobID int primary key auto_increment, 
CameraID varchar(20),
ProductName Varchar(255) not null ,
TaughtValue Varchar(255) not null,
StartTime datetime,
StopTime datetime,
GoodCount int default 0,
BadCount int default 0
);
describe jobdetails;
select * from jobdetails;
select * from pielwise;




