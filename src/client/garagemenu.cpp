#include "garagemenu.hpp"

GarageMenu::GarageMenu(QWidget *parent) :
	GameMenu(parent),
	ui(new Ui::GarageMenu)
{
	ui->setupUi(this);
}

void GarageMenu::gameStateLoaded(Client::State* state)
{
	model.reset(new VehicleTableModel(state->getPlayer()->getVehicles()));

	TableView* view = ui->carList;

	view->setModel(model.get());
	view->showColumn(model->name.getIndex());
	view->showColumn(model->price.getIndex());

	view->horizontalHeader()->setResizeMode(model->name.getIndex(), QHeaderView::Stretch);
}

void GarageMenu::on_carList_clicked(const QModelIndex& current)
{
	Game::Vehicle* vehicle = model->getObject(current.row());
	
	if(!vehicle)
		return;
	
	ui->carNameLabel->setText(vehicle->getName().c_str());
	ui->carImage->setPixmap(QPixmap(QString("gamedata/vehicleimages/") + QString(vehicle->getImageName().c_str())));
	ui->value->setText(QString::number(vehicle->getPrice()) + trUtf8(" €"));
	ui->chassisMass->setText(QString::number(vehicle->getMass()) + QString(" kg"));
	ui->engine->setText("1.0L S4 OVH\nTurbo");
	ui->fuelintake->setText("2x30mm Kaasutin");
}

void GarageMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}

