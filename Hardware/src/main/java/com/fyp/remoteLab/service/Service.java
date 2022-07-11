package com.fyp.remoteLab.service;
import com.fyp.remoteLab.model.Input;
import com.fyp.remoteLab.model.Result;
import com.fyp.remoteLab.repo.InputRepo;
import com.fyp.remoteLab.repo.ResultRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public class Service {
    @Autowired
    private InputRepo inputRepo;
    @Autowired
    private ResultRepo resultRepo;
    public ResponseEntity saveInputs(Input input) {
        List<Input> inputList= inputRepo.findAll();
        if(inputList.isEmpty()){
            inputRepo.save(input);
        }
        else{
            inputList.get(0).setCurrentLMT(input.getCurrentLMT());
            inputList.get(0).setStopVolt(input.getStopVolt());
            inputList.get(0).setIncrement(input.getIncrement());
            inputRepo.save(inputList.get(0));
        }
        return new ResponseEntity(HttpStatus.CREATED);
    }

    public ResponseEntity<Input> getData() {
        List<Input> inputList = inputRepo.findAll();
        return  new ResponseEntity<>(inputList.get(0), HttpStatus.OK);
    }

    public ResponseEntity saveResult(List<Result> result) {
        List<Result> resultList =  resultRepo.findAll();
        if (resultList.isEmpty()){
            System.out.println("\n Still empty");
            resultRepo.saveAll(result);
        }else{
            for(int i=0; i < resultList.size();i++){
                resultList.get(i).setCurrent(result.get(i).getCurrent());
                resultList.get(i).setVolt(result.get(i).getVolt());
                System.out.println(resultList.get(i));
            }
            resultRepo.saveAll(resultList);
        }
        return  new ResponseEntity(HttpStatus.CREATED);
    }
    public ResponseEntity<List<Result>> fetchResults() {
        List<Result> results = new ArrayList<>();
        List<Result> resultList = resultRepo.findAll();
        Input  input =  inputRepo.findById(Long.valueOf(1)).get();
        double volt = input.getStopVolt();
        for(int i = 0; i<resultList.size(); i++){
            System.out.println("\n\n\n"+volt);
            System.out.println("volt : "+resultList.get(i).getVolt());
            if (volt >= resultList.get(i).getVolt()){
             results.add(resultList.get(i));
            }
        }
        return  new ResponseEntity<List<Result>>(results, HttpStatus.OK);
    }
}