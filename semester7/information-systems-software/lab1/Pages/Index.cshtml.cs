using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab1.Pages;

[BindProperties]
public class IndexModel : PageModel
{   
    public IEnumerable<Student> Students { 
        get => _studentService.GetAll();
    }

    public Student NewStudent { get; set; } 

    public string Message { get; set; }

    private IStudentService _studentService;

    public IndexModel(IStudentService service)
    {
        _studentService = service;
    }

    public void OnPost()
    {
        var context = new ValidationContext(NewStudent);
        var results = new List<ValidationResult>();
        if (!Validator.TryValidateObject(NewStudent, context, results, true))
        {
            Message = "Error: ";
            foreach (var error in results)
            {
                Message += error.ErrorMessage;
            }
        }
        else
        {
            _studentService.Add(NewStudent);
            Message = "Student was added.";
        }
    }
}
