using Microsoft.AspNetCore.Mvc;
using Application.Dto;
using Application.Services.Interfaces;

namespace Api.Controllers;

[ApiController]
[Route("api/movies")]
public class MovieController : ControllerBase
{

    private readonly IMovieService _movieService;

    public MovieController(IMovieService movieService)
    {
        _movieService = movieService;    
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<MovieDto>>> Get([FromQuery]int? limit, 
        [FromQuery]int? offset, [FromQuery]float? minRating)
    {
        return new JsonResult(await _movieService.GetMoviesAsync(limit, offset, minRating));
    }

    [HttpGet("{id}")]
    public async Task<IActionResult> Get(int id)
    {
        return new JsonResult(await _movieService.GetMovieByIdAsync(id));
    }

    [HttpPost]
    public async Task<IActionResult> Post([FromForm]MovieUploadDto movieInfo)
    {
        if (movieInfo.Poster == null)
        {
            return BadRequest("Poster was not uploaded.");
        }

        if (movieInfo.Movie == null || movieInfo.Movie.Length == 0)
        {
            return BadRequest("Movie was not uploaded.");
        }

        await _movieService.UploadMovie(movieInfo);
        return Ok("Movie uploaded successfully.");
    }
}
