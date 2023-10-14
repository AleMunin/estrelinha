void loop(){
    //delay(500);
    pca_1.setPWM(0, 0, max_freq);
    delay(1000);
    //pca_1.setPWM(0, 0, 1000);
    pca_1.setPWM(0, 0, sem_brilho);

    debug_blink(100,50);


    // Gradually increase the LED brightness
    for (int brightness = 0; brightness <= 255; brightness++) {
        analogWrite(ledPin, brightness);
        delay(10); // Delay for a smoother transition
    }

    // Gradually decrease the LED brightness
    for (int brightness = 255; brightness >= 0; brightness--) {
        analogWrite(ledPin, brightness);
        delay(10); // Delay for a smoother transition
    }
}
