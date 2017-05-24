int pieza[8][4][5][5]=
  {
    //primera pieza
    {
      //primera rotacion
      {{1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rotacion
      {{1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //tercera rotacion
      {{1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //cuarta rotacion
      {{1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0}, 
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    },
    //segunda pieza
    {
      //primera rot
      {{1, 1, 1, 0, 0}, 
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{1, 0, 0, 0, 0}, 
       {1, 0, 0, 0, 0},
       {1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }, 
      //tercera rot
      {{1, 1, 1, 0, 0}, 
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //ultima rot
      {{1, 0, 0, 0, 0}, 
       {1, 0, 0, 0, 0},
       {1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    },
    //tercera pieza
    {
      //primera rot
      {{1, 1, 1, 0, 0}, 
       {1, 0, 0, 0, 0},
       {1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{1, 1, 1, 0, 0}, 
       {0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //tercera rot
      {{0, 0, 1, 0, 0}, 
       {0, 0, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //ultimaa rot
      {{1, 0, 0, 0, 0}, 
       {1, 0, 0, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    },
    //cuarta pieza
    {
      //primera rot
      {{1, 1, 1, 0, 0},
       {1, 1, 1, 1, 1},
       {1, 1, 1, 0, 0}, 
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0}, 
       {0, 1, 0, 0, 0},
       {0, 1, 0, 0, 0}
      },
      //tercera rot
      {{0, 1, 0, 0, 0},
       {0, 1, 0, 0, 0},
       {1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0}
      },
      //ultima rot
      {{0, 0, 1, 1, 1},
       {1, 1, 1, 1, 1},
       {0, 0, 1, 1, 1},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    },
    //quita pieza
    {
      //primera rot
      {{1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //tercera rot
      {{1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //cuarta rot    
      {{1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    },
    //sexta pieza
    {
      //primera rot
      {{1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //tercera rot     
      {{1, 1, 1, 0, 0},
       {0, 1, 1, 0, 0},
       {0, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //cuarta rot
      {{0, 0, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
    },
    //septima pieza
    {
      //primera rot
      {{1, 1, 1, 0, 0},
       {0, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{0, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //tercera rot
      {{1, 1, 0, 0, 0},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //ultima rot
      {{1, 1, 0, 0, 0},
       {1, 1, 0, 0, 0},
       {1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    },
    //ultima pieza
    {    
      //primera rot
      {{1, 1, 1, 0, 0}, 
       {0, 1, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //segunda rot
      {{1, 0, 0, 0, 0}, 
       {1, 1, 0, 0, 0},
       {1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //tercera rot
      {{0, 1, 0, 0, 0}, 
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      },
      //ultima rot
      {{0, 1, 0, 0, 0}, 
       {1, 1, 0, 0, 0},
       {0, 1, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}
      }
    }
  };
  

    