*** Procedure(프로시져)

--자주 실행되는 SQL & PL/SQL을 미리 컴파일하여 저장한 객체->호출(실행)만 하여 사용
--APP에서 가장 많이 사용되는 객체(개발자***)

--목적:데이터 처리(변경=DML)->대상 테이블이 존재***
        성능 향상(속도 빠르다)->한 번의 컴파일로 호출만 해서 사용
        메모리 절약->동일한 프로시져를 여러 사용자가 호출하더라도 하나의 메모리 사용

--테이블이 아닌 프로시져 단위의 사용권한을 부여하므로 보안성을 강화
grant select, insert, update, delete on gogek to scott;
grant execute on gogek_p to scott;

--파라미터 변수 mode(type만 지정!-길이 지정 안 함)
  -in mode	: 호출될 때 값이 받는 변수***
  -out mode	: 프로시져가 실행된 결과값을 넘겨주는 변수(호출자)
  -in out mode	: 값을 받아 실행된 후 결과를 다시 넘겨주는 변수	

--형식
create or replace procedure pro_name
	(파라미터 변수 [(in)|out|in out] type,....)         // [] : 생략되어있음, type은 길이를 지정할 수 없음
is
--지역 변수 선언;
begin
	명령;
end;
/

--에러정보
show error procedure pro_name
user_errors 뷰
