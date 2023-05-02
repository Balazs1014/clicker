#include "Autoclicker.hpp"
#include "DnsCacheFlusher.hpp"
#include "PrefetchCleaner.hpp"
#include "UI.hpp"

int main() {
	UI ui = UI();
	ui.printLogo();
	Autoclicker clicker = Autoclicker();
	clicker.setCps(ui.askForNumberInRange(1, 15));
	ui.showMessageBox("Everything set ready?");
	clicker.setToggleKey(VK_INSERT);
	clicker.start();
	ui.showMessageBox("Fucky wacky we broke out of loop");
}