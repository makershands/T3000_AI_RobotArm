function 좌표이동 (도착위치: any[], 속도: number) {
    while (!(배열동일여부(모터각도, 도착위치))) {
        for (let index = 0; index <= 2; index++) {
            if (모터각도[index + 1] < 도착위치[index]) {
                모터각도[index + 1] = 모터각도[index + 1] + 1
            } else if (모터각도[index + 1] > 도착위치[index]) {
                모터각도[index + 1] = 모터각도[index + 1] - 1
            }
        }
        basic.pause(속도)
    }
}
function 배열동일여부 (배열1: any[], 배열2: any[]) {
    for (let index2 = 0; index2 <= 2; index2++) {
        if (배열1[index2 + 1] != 배열2[index2]) {
            return false
        }
    }
    return true
}
function 집기 (속도: number) {
    while (모터각도[0] != 96) {
        모터각도[0] = 모터각도[0] + 1
        basic.pause(속도)
    }
}
function 색깔이동 (색깔위치: any[]) {
    놓기(모터이동속도 / 2)
    좌표이동(초기위치, 모터이동속도)
    좌표이동(공위치, 모터이동속도)
    집기(모터이동속도 / 2)
    basic.pause(100)
    좌표이동(초기위치, 모터이동속도)
    좌표이동(색깔위치, 모터이동속도)
    놓기(모터이동속도 / 2)
    좌표이동(초기위치, 모터이동속도)
    집기(모터이동속도 / 2)
}
bluetooth.onBluetoothConnected(function () {
    basic.showIcon(IconNames.Happy)
    basic.pause(100)
    bluetooth.startUartService()
})
bluetooth.onBluetoothDisconnected(function () {
    basic.showIcon(IconNames.Sad)
    basic.pause(100)
})
function 소리재생 (라벨: string) {
    if (!(music.isSoundPlaying())) {
        if (라벨 == "White") {
            music.play(music.stringPlayable("A F E F D G E F ", 500), music.PlaybackMode.LoopingInBackground)
        } else if (라벨 == "Orange") {
            music.play(music.stringPlayable("E B C5 A B G A F ", 500), music.PlaybackMode.LoopingInBackground)
        } else {
            music.play(music.stringPlayable("C5 B A G F E D C ", 500), music.PlaybackMode.LoopingInBackground)
        }
    }
}
function 검증 (모터: number, 각도: number) {
    if (각도 <= 각도한계[모터 * 2]) {
        return 각도한계[모터 * 2]
    } else if (각도 >= 각도한계[모터 * 2 + 1]) {
        return 각도한계[모터 * 2 + 1]
    } else {
        return 각도
    }
}
function 조이스틱모드 (받은문자: string) {
    모터 = parseFloat(받은문자.charAt(0))
    상태 = parseFloat(받은문자.substr(1, 2))
    모터상태[모터] = 상태
    if (상태 != 0) {
        소리재생(받은문자)
        이미지[모터 * 2 + 0.5 + 상태 * 0.5].showImage(0)
    }
    if (배열동일여부(모터상태, [0, 0, 0])) {
        if (모터상태[0] == 0) {
            basic.clearScreen()
            music.stopMelody(MelodyStopOptions.All)
        }
    }
}
function 색인식모드 (라벨: string) {
    if (라벨 == "White") {
        라벨이미지[0].showImage(0)
        소리재생(라벨)
        색깔이동(흰색)
        music.stopMelody(MelodyStopOptions.All)
    } else if (라벨 == "Orange") {
        라벨이미지[1].showImage(0)
        소리재생(라벨)
        색깔이동(오렌지색)
        music.stopMelody(MelodyStopOptions.All)
    } else if (라벨 == "None") {
        라벨이미지[2].showImage(0)
    } else {
        basic.clearScreen()
    }
}
bluetooth.onUartDataReceived(serial.delimiters(Delimiters.Hash), function () {
    받은문자 = bluetooth.uartReadUntil(serial.delimiters(Delimiters.Hash))
    if (라벨.indexOf(받은문자) != -1) {
        색인식모드(받은문자)
        조이스틱인가 = false
    } else {
        조이스틱모드(받은문자)
        조이스틱인가 = true
    }
})
function 놓기 (속도: number) {
    while (모터각도[0] != 0) {
        모터각도[0] = 모터각도[0] - 1
        basic.pause(속도)
    }
}
/**
 * 문자들어오는형식
 * 
 * (번호)(부호)(상태)
 * 
 * 예시
 * 
 * 1번 모터가 증가일때 -> 0+1
 * 
 * 4번 모터가 감소일때 -> 3-1
 * 
 * 2번 모터가 멈춤일때 -> 1+0
 * 
 * 이미지 배열 저장방식(실제 모터값 기준)
 * 
 * [1번감소, 1번증가, 2번감소, ... , 4번증가]
 * 
 * 각도한계
 * 
 * [1번최저, 1번최고, 2번최저, ..., 4번최고]
 * 
 * 핀맵
 * 
 * 전 모터 90도일 때 기준, 맨 위부터 1번 모터
 * 
 * 1번모터->15번
 * 
 * 2번모터->16번
 * 
 * 3번모터->5번
 * 
 * 4번모터->2번
 */
let 받은문자 = ""
let 상태 = 0
let 모터 = 0
let 이미지: Image[] = []
let 라벨이미지: Image[] = []
let 각도한계: number[] = []
let 모터각도: number[] = []
let 모터상태: number[] = []
let 초기위치: number[] = []
let 오렌지색: number[] = []
let 흰색: number[] = []
let 공위치: number[] = []
let 라벨: string[] = []
let 모터이동속도 = 0
let 조이스틱인가 = false
basic.showIcon(IconNames.Asleep)
basic.pause(100)
조이스틱인가 = false
모터이동속도 = 16
라벨 = ["White", "Orange", "None"]
공위치 = [65, 180, 90]
흰색 = [40, 120, 10]
오렌지색 = [40, 120, 180]
초기위치 = [90, 90, 90]
모터상태 = [
0,
0,
0,
0
]
모터각도 = [
90,
90,
90,
90
]
각도한계 = [
0,
96,
0,
180,
90,
180,
15,
180
]
라벨이미지 = [images.createImage(`
    . . # . .
    . # . # .
    # . . . #
    . # . # .
    . . # . .
    `), images.createImage(`
    . . # . .
    . . # . .
    # # # # #
    . . # . .
    . . # . .
    `), images.createImage(`
    # . . . #
    . # . # .
    . . . . .
    . # . # .
    # . . . #
    `)]
이미지 = [
images.createImage(`
    . . . . .
    . # . # .
    # . . . #
    . # . # .
    . . . . .
    `),
images.createImage(`
    . . . . .
    # . . . #
    . # . # .
    # . . . #
    . . . . .
    `),
images.createImage(`
    . . . . .
    . . . . .
    # . . . #
    . # . # .
    . . # . .
    `),
images.createImage(`
    . . # . .
    . # . # .
    # . . . #
    . . . . .
    . . . . .
    `),
images.createImage(`
    . . # . .
    . # # # .
    # . # . #
    . . # . .
    . . # . .
    `),
images.createImage(`
    . . # . .
    . . # . .
    # . # . #
    . # # # .
    . . # . .
    `),
images.createImage(`
    . . # . .
    . . . # .
    # # # # #
    . . . # .
    . . # . .
    `),
images.createImage(`
    . . # . .
    . # . . .
    # # # # #
    . # . . .
    . . # . .
    `)
]
basic.forever(function () {
    if (조이스틱인가) {
        for (let index3 = 0; index3 <= 3; index3++) {
            모터각도[index3] = 검증(index3, 모터각도[index3] + 모터상태[index3])
            basic.pause(2)
        }
    }
    pins.servoWritePin(AnalogPin.P15, 모터각도[0])
    pins.servoWritePin(AnalogPin.P16, 모터각도[1])
    pins.servoWritePin(AnalogPin.P5, 모터각도[2])
    pins.servoWritePin(AnalogPin.P2, 모터각도[3])
    bluetooth.uartWriteString("" + 모터각도[0] + " : " + 모터각도[1] + " : " + 모터각도[2] + " : " + 모터각도[3])
})
