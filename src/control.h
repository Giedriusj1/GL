
namespace controlspace {

void keyPressed(unsigned char key, int mousePositionX, int mousePositionY);
void keyReleased(unsigned char key, int mousePositionX, int mousePositionY);
void mouseRotateCamera(int x, int y);
void setCoordinates(float *eX, float *eY, float *eZ, float *oX, float *oY,
                    float *oZ, float timeDelta);
void updateCamera();
} // namespace controlspace
