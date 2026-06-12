# DataMonitor-SangminHan-24070448

> **[POC Stage]** 현재 개념 검증(Proof of Concept) 단계입니다. 구현 코드는 포함되지 않습니다.

## POC: 데이터 모니터링 Tool

현재 저장된 데이터 상태를 콘솔에서 실시간 조회할 수 있는 관리자 도구 PoC 레포지토리입니다.

## 개발 환경

- **언어**: C++
- **IDE**: Visual Studio

## 목적

- 저장된 시료·주문 데이터를 콘솔에서 실시간 조회하는 구조 검증
- 상태별(RESERVED / PRODUCING / CONFIRMED / RELEASE) 주문 현황 표시
- 시료별 재고 현황 (여유 / 부족 / 고갈) 표시

## 폴더 구조

```
DataMonitor-SangminHan-24070448/
  src/
    monitor/   - 데이터 읽기 및 집계 로직 (*.h, *.cpp)
    display/   - 콘솔 출력 포맷 처리 (*.h, *.cpp)
  DataMonitor.sln
```

## 빌드 및 실행 결과

```
[ 주문량 현황 ]
  RESERVED  : 2건
  PRODUCING : 1건
  CONFIRMED : 1건
  RELEASE   : 1건  (REJECTED 제외 확인)

[ 재고 현황 ]
  S-001 실리콘 웨이퍼-8인치  480ea  대기150ea  [여유]
  S-003 SiC 파워기판-6인치    30ea  대기200ea  [부족]
  S-004 산화막 웨이퍼-SiO2     0ea  대기  0ea  [고갈]
```

- Build: MSBuild Debug|x64 — 에러/경고 없음
- 여유/부족/고갈 상태 분류 및 REJECTED 제외 로직 검증 완료

## 표시 항목

| 항목 | 내용 |
|------|------|
| 주문량 현황 | 상태별 주문 건수 (REJECTED 제외) |
| 재고 현황 | 시료별 재고 수량 및 여유/부족/고갈 상태 |
