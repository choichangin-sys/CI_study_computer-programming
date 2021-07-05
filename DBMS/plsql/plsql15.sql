--전체 이름을 가지고 이름을 제외한 성만 추출하는 함수
create or replace function f_name
	(v_name varchar2)
	return varchar2
is
begin
	return substr(v_name, 1, 1);
end;
/


















