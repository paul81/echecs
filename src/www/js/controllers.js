'use strict';

/* Controllers */


var app = angular.module('myApp.controllers', []);



app.controller('sideLeft', ['$scope','$mdSidenav','$location','fileDialog','File','ModalWindow','$mdBottomSheet','Grille','FileExplorateur', function($scope,$mdSidenav,$location, fileDialog, File, ModalWindow, $mdBottomSheet,Grille,FileExplorateur){

    $scope.data = [
        {
            'name':'Charger une partie',
            func: function(){
                load();
            }
        },
        {
            'name':'Sauvegarder une partie',
            func: function(){
                save();
            }
        }
    ];
    $scope.close = function() {
        $mdSidenav('left').close();
    };

    $scope.toggleLeft = function() {
        $mdSidenav('left').toggle();
    };


    $scope.toggleBottom = function(){
        $scope.items = [0,1,2];
        $mdBottomSheet.show({
            templateUrl: 'template/bottom.html'
        }).then(function(clickedItem) {

        });
    }

    var load = function() {
        FileExplorateur.load();
    };

    var save = function() {
        var name = ModalWindow.save('dialogSave', function(d){
            var code = File.saveFile(d, d.length);
        });
    };


}]);



app.controller('menu',['$scope','$location','ModalWindow',function($scope,$location,ModalWindow){

    $scope.launch = 0;
    $scope.modal = {
        message: "Erreur lors de l'ouverture du fichier",
        title: "Erreur"
    };


    ModalWindow.start('start');

    $scope.go = function(url){
        $location.path(url);
    }




    $scope.setIa = function(){
        ModalWindow.showAdvanced('modal');
    }





}]);


app.controller('grille', function ($scope, Grille, ModalWindow, FileExplorateur, $routeParams) {


        $scope.alertJoueur = "Ce n'est pas votre tour ! ";


        var data = window.tab ||
            [
                {type: 'R', ligne:5, colonne: 2, joueur: 0},
                {type: 'D', ligne:4, colonne: 3, joueur: 1},
                {type: 'T', ligne:3, colonne: 4, joueur: 0},
                {type: 'F', ligne:2, colonne: 0, joueur: 1},
                {type: 'C', ligne:1, colonne: 2, joueur: 1},
                {type: 'P', ligne:1, colonne: 3, joueur: 0}
            ];

        var svg = d3.select('#svg').append('g');


        var drag = d3.behavior.drag()
            .on('drag', dragmove)
            .on('dragend', dragend);


        var pieces = svg.selectAll('piece').data(data);


        pieces.enter()
            .append('svg:image')
            .attr('xlink:href', icone)
            .attr('width', '50px')
            .attr('height', '50px')
            .attr('x', positionX)
            .attr('y', positionY)
            .call(drag);


        $scope.modal = {
            message: "",
            title: ""
        };
        $scope.repeat = false;


        var init = function(){

            data = window.tab ||
                [
                    {type: 'R', ligne:5, colonne: 2, joueur: 0},
                    {type: 'D', ligne:4, colonne: 3, joueur: 1},
                    {type: 'T', ligne:3, colonne: 4, joueur: 0},
                    {type: 'F', ligne:2, colonne: 0, joueur: 1},
                    {type: 'C', ligne:1, colonne: 2, joueur: 1},
                    {type: 'P', ligne:1, colonne: 3, joueur: 0}
                ];

            svg.remove();
            svg = d3.select('#svg').append('g');


            drag = d3.behavior.drag()
                .on('drag', dragmove)
                .on('dragend', dragend);


            pieces = svg.selectAll('piece').data(data);


            pieces.enter()
                .append('svg:image')
                .attr('xlink:href', icone)
                .attr('width', '50px')
                .attr('height', '50px')
                .attr('x', positionX)
                .attr('y', positionY)
                .call(drag);

            /*pieces[0].forEach(function (d) {
                var piece = d3.select(d)[0][0].__data__;
                var val = window.checkCase(piece.colonne, piece.ligne);
                if (!val) {
                    d3.select(d).remove();
                } else if ((piece.joueur + 1) != val) {
                    d3.select(d).remove();
                }
            });*/

        };

        Grille.init(init);




        function positionX (d) {
            return 60 + 76 * d.colonne + 'px';
        }





        function positionY (d) {
            return 50 + 78 * d.ligne + 'px';
        }





        function icone(d) {
            var url = "";
            var couleur = 'l';
            if (d.joueur == 1) couleur = 'd';
            switch(String.fromCharCode(d.type)) {
                case 'R':
                    url = "img/svg/Chess_k" + couleur + "t45.svg";
                    break;
                case 'D':
                    url = "img/svg/Chess_q" + couleur + "t45.svg";
                    break;
                case 'F':
                    url = "img/svg/Chess_b" + couleur + "t45.svg";
                    break;
                case 'C':
                    url = "img/svg/Chess_n" + couleur + "t45.svg";
                    break;
                case 'T':
                    url = "img/svg/Chess_r" + couleur + "t45.svg";
                    break;
                case 'P':
                    url = "img/svg/Chess_p" + couleur + "t45.svg";
                    break;
            }
            return url;
        }






        function dragmove (d) {
            d3.select(this)
                .attr('x', d3.event.x - 20)
                .attr('y', d3.event.y - 20);
        }







        var checkPiece = function(d,dx,dy) {
            var piece;
            d.colonne = dx;
            d.ligne = dy;
            pieces[0].forEach(function (d) {
                piece = d3.select(d)[0][0].__data__;
                var val = window.checkCase(piece.colonne, piece.ligne);
                if (!val) {
                    d3.select(d).remove();
                } else if ((piece.joueur + 1) != val) {
                    d3.select(d).remove();
                }
            });
        };





        var updatePiece = function(d,dx,dy,posX,posY,direction) {
            var piece;
            d.colonne = dx;
            d.ligne = dy;
            pieces[0].forEach(function (d) {
                piece = d3.select(d)[0][0].__data__;
                if (piece.colonne == posX && piece.ligne == posY) {
                    piece.colonne = dx + direction;
                    piece.ligne = dy;
                }
            });
        };






        var promoPiece = function(d, retour) {
            if (retour == 300) {
                $scope.path = ["img/svg/Chess_blt45.svg","img/svg/Chess_qlt45.svg", "img/svg/Chess_nlt45.svg","img/svg/Chess_rlt45.svg"];
            } else if (retour == 301) {
                $scope.path = ["img/svg/Chess_bdt45.svg","img/svg/Chess_qdt45.svg", "img/svg/Chess_ndt45.svg","img/svg/Chess_rdt45.svg"];
            }
            $scope.modal.title = "Promotion";
            $scope.modal.message = "Veuillez choisir une pièce.";
            $scope.$digest();
            d.promu = true;
        };






        var finJeu = function(retour) {
            $scope.modal.title = "fin de jeu ";
            switch (retour) {
                case 100:
                    $scope.modal.message = "Le joueur noir à gagner avec un echecs et mat";
                    break;
                case 101:
                    $scope.modal.message = "Le joueur blanc à gagner avec un echecs et mat";
                    break;
                case 102:
                    $scope.modal.message = "Le joueur noir à mis le joueur blanc en pat : Egalité";
                    break;
                case 103:
                    $scope.modal.message = "Le joueur blanc à mis le joueur noir en pat : Egalité";
                    break;
            }
            $scope.$digest();
        };





        var calculPos = function(retour){

            function setPosition(posX, posY, direction) {
                this.posX = posX;
                this.posY = posY;
                this.direction = direction;
            }

            switch (retour) {
                case 200:
                    var data = new setPosition(0,7,1);
                    break;
                case 201:
                    var data = new setPosition(0,0,1);
                    break;
                case 202:
                    var data = new setPosition(7,7,-1);
                    break;
                case 203:
                    var data = new setPosition(7,0,-1);
                    break;
            }
            return data;
        };


        function dragend (d) {
            if(this.deplacementEnCours) return;
            this.deplacementEnCours = true;
            var retour = 1;
            var x = d3.select(this).attr('x');
            var y = d3.select(this).attr('y');
            var dx = Math.floor((x - 40) / 72 );
            var dy = Math.floor((y - 40) / 70 );
            if (dx >= 0 && dx <= 7 && dy >= 0 && dy <= 7)
                retour = Grille.deplace(d.colonne, d.ligne, dx, dy);
            if (retour == 0) {
                checkPiece(d,dx,dy);
            } else if (retour >= 100 && retour <= 103) {
                finJeu(retour);
                $("#firstModal").foundation("reveal", "open");
            } else if (retour >=200 && retour <= 203) {
                var p = calculPos(retour);
                updatePiece(d,dx,dy, p.posX, p.posY, p.direction);
            } else if (retour == 300 || retour == 301) {
                checkPiece(d,dx,dy);
                promoPiece(d, retour);
                $("#PromoModal").foundation("reveal", "open");
            } else if (retour == 3) {
                $('#alertJoueur').foundation("reveal", "open");
                ModalWindow.showAdvanced('alertJoueur');
            } else if (retour == 400) {
                $scope.alertJoueurRepet = "Triple répétition pour le joueur noir";
                $scope.$digest();
                ModalWindow.showAdvanced('alertJoueurRepet1');
                $('#alertJoueurRepet').foundation("reveal", "open");
                checkPiece(d,dx,dy);
            } else if (retour == 401) {
                $scope.alertJoueurRepet = "Triple répétition pour le joueur blanc";
                $scope.$digest();
                $('#alertJoueurRepet').foundation("reveal", "open");
                checkPiece(d,dx,dy);
            }
            svg.selectAll('image').transition().attr('x', positionX).attr('y', positionY);
            this.deplacementEnCours = false;
        }



    var setImagePion = function(index,colonne,ligne,piecePromu) {
        switch (index) {
            case 0:
                Grille.promotion('F'.charCodeAt(0), colonne, ligne);
                d3.select(piecePromu).attr('xlink:href',$scope.path[index]);
                break;
            case 1:
                Grille.promotion('D'.charCodeAt(0), colonne, ligne);
                d3.select(piecePromu).attr('xlink:href',$scope.path[index]);
                break;
            case 2:
                Grille.promotion('C'.charCodeAt(0), colonne, ligne);
                d3.select(piecePromu).attr('xlink:href',$scope.path[index]);
                break;
            case 3:
                Grille.promotion('T'.charCodeAt(0), colonne, ligne);
                d3.select(piecePromu).attr('xlink:href',$scope.path[index]);
                break;
        }
    };





    $scope.changePiece = function(index) {
        var piece;
        this.getPromu = true;
        var piecePromu;
        var colonne;
        var ligne;
        pieces[0].forEach(function (d) {
            piece = d3.select(d)[0][0].__data__;
            if (piece.promu) {
                piecePromu = d;
                colonne = piece.colonne;
                ligne = piece.ligne;
                piece.promu = false;
            }
        });
        setImagePion(index,colonne,ligne,piecePromu);
        $("#PromoModal").foundation("reveal", "close");
    }


    if ($routeParams.mode == 'chargement') {
        FileExplorateur.load();
    }


});


app.controller('piecePromo', function($scope, Data){

    $scope.change = function(index){
        Data.save(index);
    }

})







