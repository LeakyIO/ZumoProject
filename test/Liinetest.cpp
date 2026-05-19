
MOtorTest motor;
Linecontroller line;
Encoder encoders;
ProxSensor prox;


void follower(){
    while (line.detected) {
        if (!encoders.leftStopped() & !encoders.rightStopped() & !prox.botsing()) {
            followLine();
        }
        else {
            motor.draaiom();
        }
    }
    else
    {
        line.searchLine();
    }

}
