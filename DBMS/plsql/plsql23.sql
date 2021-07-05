-- 사원이 급여를 변경하면. ***
-- 1. 에러 메세지 출력(급여를 변경할 수 없도록!)
-- 2. 변경한 세션명, 날짜(시간포함), 변경사원번호, 변경전 금액, 변경후 금액 정보를 black_list 테이블 입력(black_list 테이블 생성)
--    문제> 급여는 변경불가 + 기록 
-- 3. 변경하려는 급여 금액이 기존급여보다 적거나 기존급여의 10%를 초과하면 에러 출력
-- 4. 3번문제에 단, 직책이 부장은 제외

-- raise_application_error(에러번호, '메세지');		// rollback 포함, 프로그램 종료 동반
--		        20001~20999, '2048Byte'

create table black_list(username varchar2(10) default user, event_date varchar2(20) default to_char(sysdate, 'yyyy-mm-dd hh24:mi:ss'),
		   sabun number(3), 
		   sapay number(10), upsapay number(10));

create or replace trigger t_gogek_insert
	before update of sapay on sawon
	for each row
	when (new.sajob != '부장')
declare
	PRAGMA AUTONOMOUS_TRANSACTION;
begin
--	insert into black_list(sabun, sapay, upsapay) values(:new.sabun, :old.sapay, :new.sapay);
--	commit;
--	raise_application_error(-20001, '급여는 변경할 수 없으며, 변경을 시도한 기록은 남겨졌습니다!');

--  if(:new.sajob != '부장') then
   	if (:new.sapay < :old.sapay) or (:new.sapay > :old.sapay*1.5)  then
     		raise_application_error(-20001, '급여가 범위안의 값이 아닙니다!');
	end if;
end;
/