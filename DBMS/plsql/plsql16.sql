--주민번호를 가지고 성별을 추출하는 함수
create or replace function f_gender
   (v_jumin varchar2)
   return varchar2
is
begin
   if substr(v_jumin, 8, 1) = '1'  or  substr(v_jumin, 8, 1) = '3' then
   return '남자';
   else
         return '여자';
   end if;
   
end;
/