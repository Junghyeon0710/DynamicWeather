# DynamicWeather

<br>

동적으로 날씨를 관리하는 플러그인입니다.


- 지원 버전 5.4 ~ 5.6
- [데모 프로젝트](https://github.com/Junghyeon0710/DynamicWeatherDemo)
- [업데이트 노트](https://github.com/Junghyeon0710/DynamicWeather/wiki/%EC%97%85%EB%8D%B0%EC%9D%B4%ED%8A%B8-%EB%85%B8%ED%8A%B8)

<br>

## 설치
1. `zip` 파일 다운로드
2. 압축후 `Plugins` 폴더에 `DynamicWeather`로 넣기
3. 프로젝트 실행
4. 에디터에서 편집 -> 플러그인에서 `DynamicWeather`플러그인 활성화

<br>
<br>


## 사용법

<img width="2121" height="223" alt="Image" src="https://github.com/user-attachments/assets/838b2fcb-fb8f-45e2-becb-b845902eee25" />

###

- `DynamicWeather` 플러그인을 활성화 합니다.

<br>
  
<img width="584" height="627" alt="Image" src="https://github.com/user-attachments/assets/8c78855d-5da1-4944-86b4-5a0f1db0e458" />

###
  
- `SunMoonDayActor`을 찾아 레벨에 배치합니다.

<br>


<img width="762" height="267" alt="Image" src="https://github.com/user-attachments/assets/ecc72b19-a3f0-4685-ba27-99d63b4f54f0" />

###
  
  
- 기존 Lighting에셋들을 제거합니다.

<br>

###
  

## 'SunMoonDayActor`액터를 클릭 후 디테일 패널에서 값을 설정

  <img width="747" height="163" alt="Image" src="https://github.com/user-attachments/assets/258e9930-5a37-463b-b59b-23bd1af8e886" />

###
  
  
  - Day Length : 하루 주기의 전체 길이
  - Time Per Cycle : 하루 주기가 완료 되는데 걸리는 전체 시간(Day Length랑 같으면 실제 시간을 사용한다는 의미입니다.)
  - Initial Time Of Day: 하루 주기가 시작되는 시간
  - 하루는 24시간이고 게임에서는 20분이 하루 주기가 됩니다.

<br>
 
###

  <img width="745" height="453" alt="Image" src="https://github.com/user-attachments/assets/8e669b29-c318-480a-b1da-d4b30b719efa" />

###
  
  - Season Weather Category
  - HasSeason: 사게절이 있는지 물어봅니다. 4계절이 있으면 체크하세요.
  - 나머지 아래 변수들은 테스트용 입니다. 데이터에셋 설정시 자동으로 채워집니다.

<br>


  <img width="733" height="164" alt="Image" src="https://github.com/user-attachments/assets/144d53a4-3119-447b-9e13-14cda058e8f2" />

###
    
  - Day Sequnce Collections : 사계절이 없는 단순 하루만 반복되다면 여기에 데이터 에셋을 추가하세요
  - Season Weather Data Asset : 사계절이 반복된다면 여기에 데이터 에셋을 추가하세요.


<br>
<br>

## SeasonWeather Data Asset
- 데이터 에셋 값들의 대해서 설명합니다.

###
  
<img width="1875" height="1251" alt="Image" src="https://github.com/user-attachments/assets/4748a6f7-e9cd-4912-80d9-2da3b691be2d" />

###

- Season Weather Infos : 사계절 정보입니다. 봄, 여름, 가을, 겨울이니 4개 추가해주세요. 커스텀 계절이 있을시 마음대로 추가 가능합니다.
- Season Name : 계절 이름입니다.
- Start Day : 해당 계절이 시작하는 일입니다.
- Duration : 게절 주기입니다. (EX: 1~37)
- Weather Chances : 날씨 정보 및 해당 날씨가 나올 확률입니다.
  - Weather Type : 날씨 상태
  - Proocedural Day Timers : 해당 날씨일때 실행되는 기능들 모음입니다. 
  - Probaility : 해당 날씨가 걸릴 확률입니다.
 
###

Proocedural Day Timers을 조합해서 사용하세요 EX) SunPostion, Rain Activation - 비가 오며 태양 포지션 변경. 더 자세한 정보는 데모 프로젝트에서 확인하실 수 있습니다.


<br>

## 실행화면

![Image](https://github.com/user-attachments/assets/f41a3030-a86d-461a-bb5c-975bdb9e8f06)



## [위에 영상 샘플 데모 프로젝트](https://github.com/Junghyeon0710/DynamicWeatherDemo)

  

  

  
