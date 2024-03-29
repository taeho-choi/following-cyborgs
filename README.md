# Following Cyborgs (C++/OpenGL)


### 지원 플랫폼

- PC

### 프로젝트 소개

- 한국공학대학교 게임공학과의 커리큘럼인 ‘컴퓨터 그래픽스’ 과목을 수강하며 제작한 프로젝트입니다.
- C++을 기반으로 OpenGL 라이브러리를 사용하여 개발하였습니다.

### 시연 영상

https://youtu.be/JlPHUMeKaAU

# 구현 내용


- 조명 효과를 적용하여 3차원 공간감을 주었습니다.
- 사이보그가 걸어다니는 관절 애니메이션을 구현하였습니다.
- 플레이어를 제외한 사이보그들과 충돌체크, 기둥(장애물)과의 충돌체크를 적용하였습니다.
- 플레이어 중심의 원 범위에 사이보그가 들어올 경우 해당 사이보그는 점프한 후 머리 위에 느낌표를 달고 플레이어를 따라옵니다.
- 1인칭 시점과 3인칭 Back View 시점, 쿼터뷰 시점을 구현하였습니다.
- 1인칭 시점과 3인칭 Back View 시점에서 이동 시 현재 바라보고 있는 방향을 기준으로 움직이도록 w,a,s,d에 대한 이동 각을 구현하였습니다.

키보드 입력

`w,a,s,d : 캐릭터 이동`

`j : 캐릭터 점프`

`1 : 1인칭 시점 적용`
`2 : 쿼터뷰 시점 적용`
`3 : 3인칭 시점 적용`

`o,p : 카메라를 기준 y축 회전 (자전)`
`k,l : 좌표계 기준 y축 회전 (공전)`

# 코멘트


- 렌더링 파이프라인을 이해하고, 그 중 정점 쉐이더, 픽셀 쉐이더를 프로그래밍 하여 객체들을 화면에 렌더링하였습니다.
- 사이보그의 움직임과 관절들의 움직임은 OpenGL의 translate, rotate, revolve 함수를 사용하였습니다.
- 삼각함수를 사용하여 캐릭터가 바라보는 방향에 따라 이동의 축이 바뀌게 하였습니다.
- 1인칭과 3인칭 BackView 시점에서는 원근 투영(Perspective View)을, 쿼터뷰 시점에서는 직교 투영(Orthographic View)를 적용하였습니다.
