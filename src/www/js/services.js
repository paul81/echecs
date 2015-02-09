'use strict';

/* Services */


// Demonstrate how to register services
// In this case it is a simple value service.
var app = angular.module('myApp.services', []);

app.service('File',[function(){

    this.loadFile = function(data,length) {
        return window.loadFile(data, length);
    }

    this.saveFile = function(data, length) {
        return window.saveFile(data, length);
    }

}]);


app.service('Grille', [function(){


	this.getPosition = function(depart,arrive) {
        var colonne = depart[0];
        var ligne = +depart[1];
        var colonneArrive = arrive[0];
        var ligneArrive = +arrive[1];
        colonneArrive = colonneArrive.charCodeAt(0) - 97;
        colonne = colonne.charCodeAt(0) - 97;
		return window.myfunc(colonne, ligne, colonneArrive, ligneArrive);
	};





    this.deplace = function (colonneDepart, ligneDepart, colonneArrive, ligneArrive) {
        console.log('deplacement');
        var result =  window.deplacerPiece(colonneDepart, ligneDepart, colonneArrive, ligneArrive);
        console.log('retour : ' + result);
        return result;
    };




    this.promotion = function(type, colonne, ligne) {
        var result = window.promotion(type, colonne, ligne);
        return result;
    }

    var callback = undefined;

    this.launchInit = function(){
        if (callback) {
            callback();
        }
    }

    this.init = function(_callback) {
        callback = _callback;
    }


}]);

app.service('Data', [function(){

    var d = [];

    this.save = function(data){
        d = [];
        d.push(data);
    }

    this.get = function(){
        return d;
    }

}]);


app.service('ModalWindow', ['$timeout','$location', '$mdSidenav','$mdDialog','FileExplorateur', function($timeout,$location, $mdSidenav,$mdDialog, FileExplorateur){

    var data;

    this.showAdvanced = function(nom) {

        $mdDialog.show({
            clickOutsideToClose: false,
            controller: DialogController,
            templateUrl: 'template/'+nom+'.html'
        });
    };


    this.start = function(path) {
        $mdDialog.show({
            clickOutsideToClose: false,
            controller: LauncherController,
            templateUrl: 'template/'+path+'.html'
        })
    };

    this.save = function(nom, callback) {
        $mdDialog.show({
            controller: SaveController,
            templateUrl: 'template/'+nom+'.html'
        }).then(function(){
            callback(data);
        })
    };


    this.showRepet = function(nom) {
        $mdDialog.show({
            controller: DialogController,
            templateUrl: 'template/'+nom+'.html'
        })
    };


    var SaveController = function($scope, $mdDialog) {

        $scope.getFileName = function(){
            data = $scope.fichier;
            $mdDialog.hide();
        }

    }


    var DialogController = function($scope, $mdDialog) {

        $scope.validerNull = function() {
            $mdDialog.hide();
            $location.path('/');
        };
        $scope.continuer = function() {
            $mdDialog.hide();
        };
        $scope.answer = function() {
            $mdDialog.hide();
        };
    };


    var LauncherController = function($scope, $mdDialog) {

        $scope.selectionFichier = false;

        $scope.normaleGame = function(){
            $scope.selectionFichier = true;
        }

        $scope.newGame = function(){
            $location.path('/grille');
            $mdDialog.hide();
        }

        $scope.loadGame = function(){
            $location.path('/grille');
            setTimeout(function(){
                FileExplorateur.load();
            },500);
            $mdDialog.hide();
        }

    }
}]);


app.service('FileExplorateur', function(Grille, fileDialog, File){

    this.load = function(){
        fileDialog.openFile(function(d){
            d = d.split("\\");
            d = d[d.length-1];
            var code = File.loadFile(d, d.length);
            if (code != 52) {
                Grille.launchInit();
            } else {
                $('#alert').foundation("reveal","open");
            }
        },false,"*");
    }

});



