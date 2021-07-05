--Dept Table 만들기
create Table Dept(Deptno  Number(3) ,
                  Dname  Varchar2(10) , 
                  Loc  Varchar2(10),
                  constraint dept_deptno_pk primary key(deptno),
		  constraint dept_dname_uq unique(dname));

Insert Into Dept Values(10, '총무부','서울');
Insert Into Dept Values(20, '영업부','대전');
Insert Into Dept Values(30, '전산부','부산');
Insert Into Dept Values(40, '관리부', '광주');

--Sawon Table 만들기
create table sawon
(sabun number(3), 
 saname varchar2(10) not null, 
 deptno number(3), 
 sajob varchar2(10),  
 sapay number(10), 
 sahire date default sysdate, 
 sasex varchar2(4), 
 saMgr number(3) , 
 constraint sawon_sabun_PK primary key(sabun), 
 constraint sawon_deptno_FK foreign key(deptno) references dept(deptno) ON delete cascade, 
 constraint sawon_sasex_ck check(sasex in ('남자','여자')), 
 constraint sawon_saMgr_FK foreign key(samgr) references sawon(sabun)) ;

Insert Into sawon Values(1,'홍길동',10,'회장',5000,'1980/01/01','남자',null);
Insert Into sawon Values(2,'한국남',20,'부장',3000,'1988/11/01', '남자',1);
Insert Into sawon Values(3,'이순신',20,'과장',3500,'1985/03/01','남자', 2);
Insert Into sawon Values(5,'이순라',20,'사원',1200,'1990/05/01','여자', 3);
Insert Into sawon Values(7,'놀기만',20,'과장',2300,'1996/06/01','여자', 2);
Insert Into sawon Values(11,'류별나',20,'과장',1600,'1989/12/01','여자', 2);
Insert Into sawon Values(14,'채시라',20,'사원',3400,'1993/10/01','여자', 3);
Insert Into sawon Values(17,'이성계',30,'부장',2803,'1984/05/01','남자', 1);
Insert Into sawon Values(13,'무궁화',10,'부장',3000,'1996/11/01','여자', 1);
Insert Into sawon Values(19,'임꺽정',20,'사원',2200,'1988/04/01','남자', 7);
Insert Into sawon Values(20,'깨똥이',10,'과장',4500,'1990/05/01','남자', 13);
Insert Into sawon Values(6,'공부만',30,'과장',4003,'1995/05/01','남자', 17);
Insert Into sawon Values(8,'채송화',30,'대리',1703,'1992/06/01','여자', 17);
Insert Into sawon Values(12,'류명한',10,'대리',1800,'1990/10/01','남자', 20);
Insert Into sawon Values(9,'무궁화',10,'사원',1100,'1984/08/01','여자', 12);
Insert Into sawon Values(4,'이미라',30,'대리',2503,'1983/04/01','여자', 17);
Insert Into sawon Values(10,'공부해',30,'사원',1303,'1988/11/01','남자', 4);
Insert Into sawon Values(15,'최진실',10,'사원',2000,'1991/04/01','여자', 12);
Insert Into sawon Values(16,'김유신',30,'사원',400,'1981/04/01','남자', 4);
Insert Into sawon Values(18,'강감찬',30,'사원',1003,'1986/07/01','남자', 4);

--Gogek Table 만들기
create table gogek(gobun number(3), 
                   goname varchar2(10), 
                   gotel varchar2(20), 
                   gojumin varchar2(14), 
                   godam number(3));

ALTER TABLE GOGEK 
ADD constraint gogek_gobun_PK primary key(gobun);

ALTER TABLE GOGEK 
ADD constraint gogek_gojumin_UQ unique(gojumin);

ALTER TABLE GOGEK 
ADD constraint gogek_godam_FK foreign key(godam) 
references sawon(sabun);

insert into gogek values(1,'류민', '123-1234', '700113-1537915',3);
insert into gogek values(2,'강민', '343-1454', '690216-1627914',2);
insert into gogek values(3,'영희', '144-1655', '750320-2636215',null);
insert into gogek values(4,'철이', '673-1674', '770430-1234567',4);
insert into gogek values(5,'류완', '123-1674', '720521-1123675',3);
insert into gogek values(6,'캔디', '673-1764', '650725-2534566',null);
insert into gogek values(7,'똘이', '176-7677', '630608-1648614',7);
insert into gogek values(8,'쇠돌', '673-6774', '800804-1346574',9);
insert into gogek values(9,'홍이', '767-1234', '731225-1234689',13);
insert into gogek values(10,'안나','767-1677', '751015-2432168',4);
commit;