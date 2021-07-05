create table student(hakbun number(3), name varchar2(10), 
		     kor number(3), mat number(3), eng number(3));

insert into student values(101,'홍길동',90,80,60);
insert into student values(102,'박길동',80,75,60);
insert into student values(103,'이길동',90,60,60);
insert into student values(104,'김길동',55,40,60);
insert into student values(105,'최길동',70,65,100);

create table record(hakbun number(3), name varchar2(10), 
		    kor number(3), mat number(3), eng number(3),
		    total number(3), ave number(5,2), hakjum char(2), 
		    grade char(10), s_rank number(3));

--학생 테이블의 데이터를 기준으로 총점, 평균, 학점(수,..), 평가(70이상 합격), 석차 계산하여
--성적표에 입력하는 커서를 정의
declare
	cursor stud is select hakbun, name, kor, mat, eng from student;
	n_tot record.total%type;
	n_ave record.ave%type;
	v_hak record.hakjum%type;
	v_gra record.grade%type;
begin
	for i in stud loop
		n_tot := i.kor+i.mat+i.eng;	
		n_ave := n_tot/3;
	
		if n_ave >= 90 then 
			v_hak := '수';
			v_gra := '합격';
		elsif n_ave >= 80 then
			v_hak := '우';
			v_gra := '합격';
		elsif n_ave >= 70 then
			v_hak :='미';
			v_gra := '합격';
		elsif n_ave >= 60 then
			v_hak := '양';
			v_gra := '불합격';
		else v_hak:='가';
		     v_gra := '불합격';
		end if;
		
 		insert into record(hakbun, name, kor, mat, eng, total, ave, hakjum, grade) 
			values(i.hakbun, i.name, i.kor, i.mat, i.eng, n_tot, n_ave, v_hak, v_gra);
	end loop;
	commit;
--다중 커서 정의	
	declare		
		cursor rak is select hakbun, total from record;
		n_rank record.s_rank%type;
	begin
		for i in rak loop
			select count(*) into n_rank from record where total>i.total;
			n_rank := n_rank+1;
			update record set s_rank=n_rank where hakbun=i.hakbun;
			commit;
		end loop;
	end;
end;
/
