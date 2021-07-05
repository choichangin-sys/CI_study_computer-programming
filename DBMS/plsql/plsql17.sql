-- 숫자 데이터를 가지고 100의 '*'기준으로 추출하는 함수
create or replace function f_star
   (v_star number)
   return varchar2
is
begin
   return rpad('*',v_star/100,'*');
end;
/
col 급여현황 format a50
select saname, sapay, f_star(sapay) 급여현황 from sawon;
