set serveroutput on
--if ���� then
--	���;
--[elsif ���� then
--	���;
-- ....
--else ���; ]
--end if; 

--break;  // ����� ����������

--�ݺ��� : for ī��Ʈ���� in �ʱⰪ..�ִ밪 loop ~~ end loop;
--�ݺ��� : while ���� loop ~~ end loop;
--�ݺ��� : loop ~~ end loop;

-- 1~10���� ����ϱ�
declare 
	i number(3) := 1;
begin
	dbms_output.put_line('for�� �̿��� ó��');
	for i in 1..10 loop
		dbms_output.put_line('i�� �� - > ' || i );
	end loop;

	dbms_output.put_line('while�� �̿��� ó��');
	while i<=10 loop
		dbms_output.put_line('i�� ��->'|| i);
		i:=i+1;
	end loop;	

	i := 1;
	dbms_output.put_line('loop�� �̿��� ó��');
  	loop
 --          	if i >10 then
 --         		      exit;
 --          	end if;
		exit when(i>10);
           		dbms_output.put_line('i�� ��->'|| i);
           		i:=i+1;
   	end loop;
end;
/













