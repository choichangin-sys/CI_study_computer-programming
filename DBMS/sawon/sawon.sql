--Dept Table �����
create Table Dept(Deptno  Number(3) ,
                  Dname  Varchar2(10) , 
                  Loc  Varchar2(10),
                  constraint dept_deptno_pk primary key(deptno),
		  constraint dept_dname_uq unique(dname));

Insert Into Dept Values(10, '�ѹ���','����');
Insert Into Dept Values(20, '������','����');
Insert Into Dept Values(30, '�����','�λ�');
Insert Into Dept Values(40, '������', '����');

--Sawon Table �����
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
 constraint sawon_sasex_ck check(sasex in ('����','����')), 
 constraint sawon_saMgr_FK foreign key(samgr) references sawon(sabun)) ;

Insert Into sawon Values(1,'ȫ�浿',10,'ȸ��',5000,'1980/01/01','����',null);
Insert Into sawon Values(2,'�ѱ���',20,'����',3000,'1988/11/01', '����',1);
Insert Into sawon Values(3,'�̼���',20,'����',3500,'1985/03/01','����', 2);
Insert Into sawon Values(5,'�̼���',20,'���',1200,'1990/05/01','����', 3);
Insert Into sawon Values(7,'��⸸',20,'����',2300,'1996/06/01','����', 2);
Insert Into sawon Values(11,'������',20,'����',1600,'1989/12/01','����', 2);
Insert Into sawon Values(14,'ä�ö�',20,'���',3400,'1993/10/01','����', 3);
Insert Into sawon Values(17,'�̼���',30,'����',2803,'1984/05/01','����', 1);
Insert Into sawon Values(13,'����ȭ',10,'����',3000,'1996/11/01','����', 1);
Insert Into sawon Values(19,'�Ӳ���',20,'���',2200,'1988/04/01','����', 7);
Insert Into sawon Values(20,'������',10,'����',4500,'1990/05/01','����', 13);
Insert Into sawon Values(6,'���θ�',30,'����',4003,'1995/05/01','����', 17);
Insert Into sawon Values(8,'ä��ȭ',30,'�븮',1703,'1992/06/01','����', 17);
Insert Into sawon Values(12,'������',10,'�븮',1800,'1990/10/01','����', 20);
Insert Into sawon Values(9,'����ȭ',10,'���',1100,'1984/08/01','����', 12);
Insert Into sawon Values(4,'�̶̹�',30,'�븮',2503,'1983/04/01','����', 17);
Insert Into sawon Values(10,'������',30,'���',1303,'1988/11/01','����', 4);
Insert Into sawon Values(15,'������',10,'���',2000,'1991/04/01','����', 12);
Insert Into sawon Values(16,'������',30,'���',400,'1981/04/01','����', 4);
Insert Into sawon Values(18,'������',30,'���',1003,'1986/07/01','����', 4);

--Gogek Table �����
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

insert into gogek values(1,'����', '123-1234', '700113-1537915',3);
insert into gogek values(2,'����', '343-1454', '690216-1627914',2);
insert into gogek values(3,'����', '144-1655', '750320-2636215',null);
insert into gogek values(4,'ö��', '673-1674', '770430-1234567',4);
insert into gogek values(5,'����', '123-1674', '720521-1123675',3);
insert into gogek values(6,'ĵ��', '673-1764', '650725-2534566',null);
insert into gogek values(7,'����', '176-7677', '630608-1648614',7);
insert into gogek values(8,'�赹', '673-6774', '800804-1346574',9);
insert into gogek values(9,'ȫ��', '767-1234', '731225-1234689',13);
insert into gogek values(10,'�ȳ�','767-1677', '751015-2432168',4);
commit;