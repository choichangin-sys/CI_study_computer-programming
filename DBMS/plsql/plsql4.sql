--* 테이블에서 행을 가져오기(단일행) : 컬럼명은 변수로 사용할 수 없다
--select 컬럼명,... into 변수,... from 테이블명,...;

declare
	name sawon.saname%type;
begin
	select saname into name from sawon where sabun=13;
	dbms_output.put_line('이름:'|| name);
end;
/

--PL/SQL에서의 변수 선언 방법
v_loc	varchar2(10) := 'seoul';
v_name	sawon.saname%type;		// sawon.saname과 같은 type(길이) 선언
v_comm	emp.comm%type not null :=100;
v_sal	constant emp.sal%type := 1000;	// 값을 변경할 수 없는 변수(반드시 초기값)
i	sawon%rowtype;			// i.sabun, i.saname, i.sapay, ....을 한 번에 선언