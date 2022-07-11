package com.fyp.remoteLab.controller;

import com.fyp.remoteLab.model.Result;
import com.fyp.remoteLab.service.Service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@CrossOrigin(maxAge = 3600)
@RestController
@RequestMapping("/output")
public class OutputController {
    @Autowired
    private Service service;

    @PostMapping("/add")
    public ResponseEntity addData(@RequestBody List<Result> result){
        return  service.saveResult(result);
    }
    @GetMapping("/get")
    public ResponseEntity<List<Result>> getResults(){
        return  service.fetchResults();
    }
}
