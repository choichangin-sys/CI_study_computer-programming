*** Trigger(트리거) 
- 업무 자동화 가능
- 특정 테이블에 지정한 이벤트(DML)가 발생하면 자동으로 호출되는 명령들 객체(호출문 없다)
- 데이터 흐름 제어문(TCL)은 사용할 수 없다(기본값)

- 목적
1. 데이터 무결성 구현(제약조건으로 구현할 수 없는 경우)
2. 업무의 자동화(연쇄작용. 예-급여계산, 보험계산, 재고관리 등 업무에 사용)
3. 데이터 복제 기능
4. 이벤트를 발생한 세션의 감시 및 데이터 기록(보안)

- 형식
create or replace trigger tri_name
	[after | berfore] insert or delete or update on table_name
	for each row
declare
	지역변수 선언;
begin
	명령;
end;
/