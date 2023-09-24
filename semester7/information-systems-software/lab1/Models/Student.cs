using System.ComponentModel.DataAnnotations;

public class Student
{

    [Required]
    [StringLength(50, MinimumLength = 2)]
    public string Name { get; set; }

    [Required]
    [StringLength(50, MinimumLength = 2)]
    public string Surname { get; set; }
}
